
# Copyright (C) 2013  Tsutomu Uchino
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


import re
import math
import traceback
import pcbnew


def insert_zone(board, netcode, layer=None, hatch_type=None, priority=0, 
                segments=32, clearance=0.2, min_width=0.2):
    """ Inserts new zone.
        @param board Pcbnew board
        @param netcode netcode id to connect the zone
        @param layer zone layer
        @param hatch_type hatch
        @param priority fill priority of zone
        @param segments number of segments
        @param clearance zone clearance
        @param min_width minimum width of zone
        @return area
    """
    if hatch_type is None: hatch_type = pcbnew.CPolyLine.DIAGONAL_EDGE
    if layer is None: raise Exception("No layer specified")
    area = board.InsertArea(netcode, 0xffff, layer, 0, 0, hatch_type)
    area.SetIsKeepout(False)
    area.SetHatchStyle(hatch_type)
    area.SetPriority(priority)
    area.SetArcSegmentCount(segments)
    area.SetZoneClearance(pcbnew.FromMM(clearance))
    area.SetMinThickness(pcbnew.FromMM(min_width))
    
    outline = area.Outline()
    outline.DeleteCorner(0) # remove first element
    return area


def insert_keepout_zone(board, layer=None, hatch_type=None, 
                        no_tracks=True, no_vias=True, no_pour=True, priority=0):
    """ Inserts new keepout zone.
        @param board Pcbnew board
        @param layer zone layer
        @param hatch_type hatch
        @param no_tracks no track allowed
        @param no_vias no vias allowed
        @param no_pour no copper pour allowed
        @param priority fill priority of zone
        @return area
    """
    if hatch_type is None: hatch_type = pcbnew.CPolyLine.DIAGONAL_EDGE
    if layer is None: raise Exception("No layer specified")
    area = board.InsertArea(-1, 0xffff, layer, 0, 0, hatch_type)
    area.SetIsKeepout(True)
    area.SetDoNotAllowTracks(no_tracks)
    area.SetDoNotAllowVias(no_vias)
    area.SetDoNotAllowCopperPour(no_pour)
    area.SetHatchStyle(hatch_type)
    area.SetPriority(priority)
    
    outline = area.Outline()
    outline.DeleteCorner(0) # remove first element
    return area


def close_zone(board, area):
    """ Close specified zone.
        @param board Pcbnew board
        @param area zone
    """
    area.Outline().CloseLastContour()
    area.BuildFilledSolidAreasPolygons(board)


def add_arc_outline(outline, center_x, center_y, radius, start_angle, end_angle, 
            corners=32, clockwise=True):
    """ Add arc to outline.
        @param outline outline
        @param center_x center x of this arc
        @param center_y center y of this arc
        @param radius radius of this arc
        @param start_angle starting angle of this arc
        @param end_angle ending angle of this arc
        @param corners number of corners in the arc
        @param clockwise direction to proceeed the arc
    """
    import math
    cos, sin, floor = math.cos, math.sin, math.floor
    
    thi = math.radians(start_angle)
    dthi = math.radians(abs(end_angle - start_angle)) / corners
    if not clockwise:
        dthi = -dthi
    
    # calculate corners
    for i in range(corners+1):
        x = int(floor(center_x + radius * cos(thi)))
        y = int(floor(center_y + radius * sin(thi)))
        outline.AppendCorner(x, y)
        thi += dthi


def insert_circular_keepout(board, center_x, center_y, radius, corners=16, 
                            layer=None, hatch_type=None, 
                            no_tracks=True, no_vias=True, no_pour=True):
    """ Adds keepout area in polygon of approximate circle. 
        Length have to be passed in internal unit.
        @param board Pcbnew board
        @param center_x center X position
        @param center_y center Y position
        @param radius circle radius
        @param corners number of vertex
        @param layer layer index
        @param hatch_type one of NO_HATCH, DIAGONAL_FULL, DIAGONAL_EDGE
        @param no_tracks True for no tracks
        @param no_vias True for no vias
        @param no_pour True for no copper pour
    """
    if hatch_type is None: hatch_type = pcbnew.CPolyLine.NO_HATCH
    if layer is None: layer = pcbnew.F_Cu
    
    area = insert_keepout_zone(board, layer, hatch_type, 
                        no_tracks, no_vias, no_pour, priority=0)
    outline = area.Outline()
    
    cos, sin, floor = math.cos, math.sin, math.floor
    
    thi = 0
    dthi = 2 * math.pi / corners
    
    # calculate corners
    for i in range(corners):
        x = int(floor(center_x + radius * cos(thi)))
        y = int(floor(center_y + radius * sin(thi)))
        outline.AppendCorner(x, y)
        thi += dthi
    
    close_zone(board, area)


def ref_iter(board, pattern):
    """ Iterate over matched modules to pattern.
        @param board Pcbnew board
        @param pattern reference pattern
        @yield module instance
    """
    exp = re.compile(pattern)
    for mod in board.GetModules():
        if exp.match(mod.GetReference()):
            yield mod


def add_track_pos(board, layer, netcode, start_pos, end_pos, track_width, 
                    center=None, angle=0):
    """ Add track to the board.
        @param board Pcbnew board
        @param layer track is placed on
        @param netcode track netcode
        @param start_pos starting position of the track
        @param end_pos ending position of the track
        @param track_width width of this track
        @param center rotation center if required
        @param angle angle if rotated
    """
    t = pcbnew.TRACK(board)
    t.SetNetCode(netcode, False)
    t.SetLayer(layer)
    t.SetWidth(track_width)
    t.SetStart(start_pos)
    t.SetEnd(end_pos)
    if not center is None and angle > 0:
        t.Rotate(center, angle)
    board.Add(t)


def add_gnd_tracks(pattern, width):
    """ Connect GND pads.
        @param pattern matching pattern
        @param width width of track
    """
    def find_gnd_pads(mod):
        pads = [pad for pad in mod.Pads() if pad.GetPadName() == "0"]
        for i, pad in enumerate(pads):
            if pad.GetPosition() == mod.GetPosition():
                del pads[i]
                return pad, pads
    
    board = pcbnew.GetBoard()
    track_width = pcbnew.FromMM(width)
    netcode = board.GetNetcodeFromNetname("GND")
    for sw in ref_iter(board, pattern):
        layer = sw.GetLayer()
        try:
            center_gnd, gnds = find_gnd_pads(sw)
            add_track_pos(board, layer, netcode, center_gnd.GetPosition(), 
                        gnds[0].GetPosition(), track_width)
            add_track_pos(board, layer, netcode, center_gnd.GetPosition(), 
                        gnds[1].GetPosition(), track_width)
        except Exception as e:
            print(e)


def remove_gnd_tracks(pattern):
    """ Remove GND tracks between GND pads in each modules.
        @param pattern not used
    """
    board = pcbnew.GetBoard()
    center_gnd_positions = [(sw.GetPosition().x, sw.GetPosition().y) 
                                for sw in ref_iter(board, pattern)]
    remove_tracks = []
    for track in board.GetTracks():
        pos = track.GetStart()
        start_pos = pos.x, pos.y
        if start_pos in center_gnd_positions:
            remove_tracks.append(track)
    for track in remove_tracks:
        board.Remove(track)


def add_gnd_tracks_A(pattern, width, center_width, center_radius):
    """ Add GND tracks for type A pad.
        @param pattern reference pattern
        @param with width of GND track
        @param center_width width of thinner track between through holes
        @param center_radius radius of center empty space
    """
    def find_gnd_pads(mod):
        pads = [pad for pad in mod.Pads() if pad.GetPadName() == "0"]
        front_pads, back_pads = [], []
        for pad in pads:
            cus = tuple(pad.GetLayerSet().CuStack())
            if pcbnew.F_Cu in cus:
                front_pads.append(pad.GetPosition())
            elif pcbnew.B_Cu in cus:
                back_pads.append(pad.GetPosition())
        if front_pads[0] != back_pads[0]:
            back_pads[0], back_pads[1] = back_pads[1], back_pads[0]
        return front_pads, back_pads
    
    def distance(pos, x, y):
        return sqrt((pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y))
        
    wxPoint = pcbnew.wxPoint
    layer_inverter = {pcbnew.F_Cu: pcbnew.B_Cu, pcbnew.B_Cu: pcbnew.F_Cu}
    track_width = pcbnew.FromMM(width)
    center_track_width = pcbnew.FromMM(center_width)
    center_r = pcbnew.FromMM(center_radius)
    sin, cos, radians, pi, sqrt = math.sin, math.cos, math.radians, math.pi, math.sqrt
    
    board = pcbnew.GetBoard()
    gnd_netcode = board.GetNetcodeFromNetname("GND")
    
    for sw in ref_iter(board, pattern):
        pos = sw.GetPosition()
        layer = sw.GetLayer()
        another_layer = layer_inverter[layer]
        orientation = sw.GetOrientation()
        rad = radians(orientation / 10.)
        try:
            front_pads, back_pads = find_gnd_pads(sw)
            x1 = center_r * cos(rad + pi * 0.5) + pos.x
            y1 = center_r * sin(rad + pi * 0.5) + pos.y
            x2 = center_r * cos(rad + pi * 1.5) + pos.x
            y2 = center_r * sin(rad + pi * 1.5) + pos.y
            # calculate distance and add trace between nearest pad and position
            if distance(front_pads[0], x1, y1) < distance(front_pads[0], x2, y2):
                xa, ya = x1, y1
                xb, yb = x2, y2
            else:
                xa, ya = x2, y2
                xb, yb = x1, y1
            add_track_pos(board, layer, gnd_netcode, front_pads[0], 
                            wxPoint(xa, ya), track_width)
            add_track_pos(board, layer, gnd_netcode, wxPoint(xa, ya), 
                            wxPoint(xb, yb), center_track_width)
            add_track_pos(board, layer, gnd_netcode, wxPoint(xb, yb), 
                            front_pads[1], track_width)
            
            add_track_pos(board, another_layer, gnd_netcode, back_pads[0], 
                            wxPoint(xa, ya), track_width)
            add_track_pos(board, another_layer, gnd_netcode, wxPoint(xa, ya), 
                            wxPoint(xb, yb), center_track_width)
            add_track_pos(board, another_layer, gnd_netcode, wxPoint(xb, yb), 
                            back_pads[1], track_width)
        except Exception as e:
            print(e)


def remove_gnd_tracks_A(pattern):
    """ Remove GND tracks from type A pad.
        @param pattern reference pattern
    """
    board = pcbnew.GetBoard()
    f_cu, b_cu = pcbnew.F_Cu, pcbnew.B_Cu
    
    def pos_to_tuple(pos):
        return pos.x, pos.y
    
    gnd_positions = []
    for sw in ref_iter(board, pattern):
        pads = [pad for pad in sw.Pads() if pad.GetPadName() == "0"]
        front_pads = [pad.GetPosition() for pad in pads if f_cu in pad.GetLayerSet().CuStack()]
        gnd_positions.append(front_pads)
    
    remove_tracks = []
    
    gnd_netcode = board.GetNetcodeFromNetname("GND")
    
    tracks = list(board.TracksInNet(gnd_netcode))
    # todo, only first track can be returned
    # todo, GND tracks can not be found before DRC
    def find_track(start_pos, layer):
        for track in tracks:
            if track.GetLayer() == layer and track.GetStart() == start_pos:
                return track
        return None
    
    for layer in (f_cu, b_cu):
        for pad0, pad1 in gnd_positions:
            start_pad = pad0
            end_pad = pad1
            track = find_track(start_pad, layer)
            if not track:
                start_pad, end_pad = end_pad, start_pad
                track = find_track(start_pad, layer)
                if track is None:
                    continue
            # find middle track
            middle_track = find_track(track.GetEnd(), layer)
            if middle_track:
                # find last track
                end_track = find_track(middle_track.GetEnd(), layer)
                if end_track.GetEnd() == end_pad:
                    remove_tracks.append(track)
                    remove_tracks.append(middle_track)
                    remove_tracks.append(end_track)
    
    for track in remove_tracks:
        board.Remove(track)


def add_back_keepout(pattern, corners, radius, no_tracks=True):
    """ Add keepout area under the pads.
        @param corners number of corners in approximate circle
        @param radius circle radius
    """
    r = pcbnew.FromMM(radius)
    hatch_type = pcbnew.CPolyLine.NO_HATCH
    layer_inverter = {pcbnew.F_Cu: pcbnew.B_Cu, pcbnew.B_Cu: pcbnew.F_Cu}
    
    board = pcbnew.GetBoard()
    for sw in ref_iter(board, pattern):
        try:
            pos = sw.GetPosition()
            insert_circular_keepout(board, pos.x, pos.y, r, 
                    corners, layer_inverter[sw.GetLayer()], 
                    hatch_type=hatch_type, no_tracks=no_tracks, no_vias=True, no_pour=True)
            # no need to rotate circular keepout area
        except Exception as e:
            print(e)


def remove_back_keepout(pattern, corners):
    """ Remove keepout area from under the pads.
        @param pattern not used
        @param corners number of corners in approximate circle
    """
    remove_areas = []
    board = pcbnew.GetBoard()
    for i in range(board.GetAreaCount()):
        area = board.GetArea(i)
        if area.GetNumCorners() == corners:
            remove_areas.append(area)
    for area in remove_areas:
        board.Remove(area)


def add_back_keepout_A(pattern, corners, outer_radius, gap, no_tracks=True):
    """ Adds keepout area on bottom side for type A pad.
        @param pattern reference pattern
        @param corners number of corners in an arc
        @param outer_radius radius of pad outer shape
        @param gap width of gap between inner pads
        @param no_tracks track is not allowed in this keepout area if True
    """
    gap_side = gap / 2.
    gap_corner = 0.2
    
    gap_outer_side = gap_side + gap_corner
    outer_start_angle = math.degrees(math.acos(gap_side / outer_radius))
    
    outer_r = pcbnew.FromMM(outer_radius)
    gap_corner_chamfer = pcbnew.FromMM(gap_corner)
    
    hatch_type = pcbnew.CPolyLine.NO_HATCH
    layer_inverter = {pcbnew.F_Cu: pcbnew.B_Cu, pcbnew.B_Cu: pcbnew.F_Cu}
    
    def swap_corner(outline, a, b):
        x, y = outline.GetX(a), outline.GetY(a)
        outline.SetX(a, outline.GetX(b))
        outline.SetY(a, outline.GetY(b))
        outline.SetX(b, x)
        outline.SetY(b, y)
    
    board = pcbnew.GetBoard()
    for sw in ref_iter(board, pattern):
        try:
            pos = sw.GetPosition()
            layer = layer_inverter[sw.GetLayer()]
            orientation = sw.GetOrientation()
            
            # right
            area = insert_keepout_zone(board, layer, hatch_type, no_tracks=no_tracks, priority=1)
            outline = area.Outline()
            add_arc_outline(outline, pos.x, pos.y, outer_r, 
                        -outer_start_angle, outer_start_angle, corners=corners, clockwise=True)
            
            outline.InsertCorner(corners, pos.x + gap_corner_chamfer, 
                                outline.GetY(corners) - gap_corner_chamfer)
            outline.InsertCorner(0, pos.x + gap_corner_chamfer, 
                                outline.GetY(0) + gap_corner_chamfer)
            # swap corner between 0 and 1, no way to put corner at zero by insertion
            swap_corner(outline, 0, 1)
            
            close_zone(board, area)
            if orientation != 0:
                area.Rotate(pos, orientation)
            
            # left
            area = insert_keepout_zone(board, layer, hatch_type, no_tracks=no_tracks, priority=1)
            outline = area.Outline()
            add_arc_outline(outline, pos.x, pos.y, outer_r, 
                        -outer_start_angle+180, outer_start_angle+180, corners=corners, clockwise=True)
            # 
            outline.InsertCorner(corners, pos.x - gap_corner_chamfer, 
                                outline.GetY(corners) + gap_corner_chamfer)
            outline.InsertCorner(0, pos.x - gap_corner_chamfer, 
                                outline.GetY(0) - gap_corner_chamfer)
            swap_corner(outline, 0, 1)
            #print(area.GetNumCorners())
            close_zone(board, area)
            if orientation != 0:
                area.Rotate(pos, orientation)
        except Exception as e:
            print(e)


def add_front_keepout(pattern, corners, outer_radius, inner_radius, gap):
    """ Adds front keepout zone.
        @param pattern matching pattern
        @param corners number of corners
        @param outer_radius radius of outer arc
        @param inner_radius radius of inner arc
        @param gap gap width between both sides
    """
    gap_side = gap / 2.
    gap_corner = 0.2
    # calculate start angle
    #outer_start_angle = math.degrees(math.acos(gap_side / (outer_radius - gap_side * gap_side)))
    gap_outer_side = gap_side + gap_corner
    outer_start_angle = math.degrees(math.acos(gap_side / outer_radius))
    inner_start_angle = math.degrees(math.acos(gap_side / inner_radius))
    
    outer_r = pcbnew.FromMM(outer_radius)
    inner_r = pcbnew.FromMM(inner_radius)
    gap_corner_chamfer = pcbnew.FromMM(gap_corner)
    
    def swap_corner(outline, a, b):
        x, y = outline.GetX(a), outline.GetY(a)
        outline.SetX(a, outline.GetX(b))
        outline.SetY(a, outline.GetY(b))
        outline.SetX(b, x)
        outline.SetY(b, y)
    
    hatch_type = pcbnew.CPolyLine.NO_HATCH
    board = pcbnew.GetBoard()
    for sw in ref_iter(board, pattern):
        try:
            pos = sw.GetPosition()
            layer = sw.GetLayer()
            orientation = sw.GetOrientation()
            
            # todo, we do not need to calculate for all sw, just copy and move it
            # right side
            area = insert_keepout_zone(board, layer, hatch_type, no_tracks=False, priority=1)
            outline = area.Outline()
            add_arc_outline(outline, pos.x, pos.y, outer_r, 
                        -outer_start_angle, outer_start_angle, corners=corners, clockwise=True)
            add_arc_outline(outline, pos.x, pos.y, inner_r, 
                        inner_start_angle, -inner_start_angle, corners=corners, clockwise=False)
            # narrow corner, InsertCorner inserts corner after the index
            outline.InsertCorner(corners, pos.x + gap_corner_chamfer, 
                                outline.GetY(corners) - gap_corner_chamfer)
            outline.InsertCorner(0, pos.x + gap_corner_chamfer, 
                                outline.GetY(0) + gap_corner_chamfer)
            # swap corner between 0 and 1, no way to put corner at zero by insertion
            swap_corner(outline, 0, 1)
            
            close_zone(board, area)
            if orientation != 0:
                area.Rotate(pos, orientation)
            
            # left side
            area = insert_keepout_zone(board, layer, hatch_type, no_tracks=False, priority=1)
            outline = area.Outline()
            add_arc_outline(outline, pos.x, pos.y, outer_r, 
                        -outer_start_angle+180, outer_start_angle+180, corners=corners, clockwise=True)
            add_arc_outline(outline, pos.x, pos.y, inner_r, 
                        inner_start_angle+180, -inner_start_angle+180, corners=corners, clockwise=False)
            # 
            outline.InsertCorner(corners, pos.x - gap_corner_chamfer, 
                                outline.GetY(corners) + gap_corner_chamfer)
            outline.InsertCorner(0, pos.x - gap_corner_chamfer, 
                                outline.GetY(0) - gap_corner_chamfer)
            swap_corner(outline, 0, 1)
            
            close_zone(board, area)
            if orientation != 0:
                area.Rotate(pos, orientation)
        except Exception as e:
            print(e)


def remove_front_keepout(pattern, corners):
    """ Remove outer keepout area on front side.
        @param pattern not used
        @param corners number of corners in keepout zone
    """
    board = pcbnew.GetBoard()
    for sw in ref_iter(board, pattern):
        layer = sw.GetLayer()
        break
    remove_areas = []
    for i in range(board.GetAreaCount()):
        area = board.GetArea(i)
        if area.GetLayer() == layer and area.GetIsKeepout() and \
            area.GetNumCorners() == corners:
            remove_areas.append(area)
    for area in remove_areas:
        board.Remove(area)


def add_front_zone_pads(pattern, corners, outer_radius, inner_radius, gap, 
                        zone_clearance=0.2, zone_min_width=0.2):
    """ Adds zones for pads.
        @param pattern matching pattern
        @param corners number of corners in outer and inner circle
        @param outer_radius radius of outer arc
        @param inner_radius radius of inner arc
        @param gap gap width between both pads
    """
    gap_side = gap / 2.
    # calculate start angle
    outer_start_angle = math.degrees(math.acos(gap_side / outer_radius))
    inner_start_angle = math.degrees(math.acos(gap_side / inner_radius))
    outer_r = pcbnew.FromMM(outer_radius)
    inner_r = pcbnew.FromMM(inner_radius)
    hatch_type = pcbnew.CPolyLine.NO_HATCH
    board = pcbnew.GetBoard()
    for sw in ref_iter(board, pattern):
        try:
            pos = sw.GetPosition()
            layer = sw.GetLayer()
            orientation = sw.GetOrientation()
            
            pad1_added = False
            pad2_added = False
            for pad in sw.Pads():
                name = pad.GetPadName()
                if name == "1" and not pad1_added:
                    # left pad
                    area = insert_zone(board, pad.GetNetCode(), layer, hatch_type, priority=1,  
                                        clearance=zone_clearance, min_width=zone_min_width)
                    add_arc_outline(area.Outline(), pos.x, pos.y, outer_r, 
                        -outer_start_angle+180, outer_start_angle+180, corners=corners, clockwise=True)
                    add_arc_outline(area.Outline(), pos.x, pos.y, inner_r, 
                                inner_start_angle+180, -inner_start_angle+180, corners=corners, clockwise=False)
                    close_zone(board, area)
                    if orientation != 0:
                        area.Rotate(pos, orientation)
                    pad1_added = True
                elif name == "2" and not pad2_added:
                    # right pad
                    area = insert_zone(board, pad.GetNetCode(), layer, hatch_type, priority=1,  
                                        clearance=zone_clearance, min_width=zone_min_width)
                    add_arc_outline(area.Outline(), pos.x, pos.y, outer_r, 
                        -outer_start_angle, outer_start_angle, corners=corners, clockwise=True)
                    add_arc_outline(area.Outline(), pos.x, pos.y, inner_r, 
                                inner_start_angle, -inner_start_angle, corners=corners, clockwise=False)
                    close_zone(board, area)
                    if orientation != 0:
                        area.Rotate(pos, orientation)
                    pad2_added = True
        except Exception as e:
            print(e)


def remove_front_zone_pads(pattern, corners):
    """ Remove pads on top side.
        @param pattern not used
        @param corners number of corners in zone
    """
    board = pcbnew.GetBoard()
    for sw in ref_iter(board, pattern):
        layer = sw.GetLayer()
        break
    remove_areas = []
    for i in range(board.GetAreaCount()):
        area = board.GetArea(i)
        if area.GetLayer() == layer and not area.GetIsKeepout() and area.GetNumCorners() == corners:
            remove_areas.append(area)
    for area in remove_areas:
        board.Remove(area)


def add_front_zone_pad_D(pattern, corners, outer_radius, inner_radius, gap,
                        zone_clearance=0.2, zone_min_width=0.2):
    """ Adds zones for pads.
        @param pattern matching pattern
        @param corners number of corners in outer and inner circle
        @param outer_radius radius of outer arc
        @param inner_radius radius of inner arc
        @param gap gap width between both pads
    """
    gap_side = gap / 2.
    # calculate start angle
    outer_start_angle = math.degrees(math.acos(gap_side / outer_radius))
    inner_start_angle = math.degrees(math.acos(gap_side / inner_radius))
    outer_r = pcbnew.FromMM(outer_radius)
    inner_r = pcbnew.FromMM(inner_radius)
    hatch_type = pcbnew.CPolyLine.NO_HATCH
    board = pcbnew.GetBoard()
    for sw in ref_iter(board, pattern):
        try:
            pos = sw.GetPosition()
            layer = sw.GetLayer()
            orientation = sw.GetOrientation()
            for pad in sw.Pads():
                name = pad.GetPadName()
                if name == "2":
                    # left pad
                    area = insert_zone(board, pad.GetNetCode(), layer, hatch_type, priority=1,  
                                        clearance=zone_clearance, min_width=zone_min_width)
                    add_arc_outline(area.Outline(), pos.x, pos.y, outer_r, 
                        -outer_start_angle-180, outer_start_angle, corners=corners, clockwise=True)
                    add_arc_outline(area.Outline(), pos.x, pos.y, inner_r, 
                        inner_start_angle, -inner_start_angle-180, corners=corners, clockwise=False)
                    close_zone(board, area)
                    if orientation != 0:
                        area.Rotate(pos, orientation)
                    break
        except Exception as e:
            print(e)


class Model:
    
    def __init__(self):
        self.settings = None # updated by the view
    
    def set_settings(self, settings):
        self.settings = settings
    
    def add_gnd_track(self):
        # needs DRC later
        s = self.settings
        if s.pad_type == "A":
            add_gnd_tracks_A(s.pattern, width=s.gap_width, 
                    center_width=s.gap_center_width, center_radius=s.gap_center_radius)
        elif s.pad_type == "D":
            return # no gnd track
        else:
            add_gnd_tracks(s.pattern, width=s.gap_width)
    
    def remove_gnd_track(self):
        s = self.settings
        if s.pad_type == "A":
            remove_gnd_tracks_A(s.pattern)
        elif s.pad_type == "D":
            return # not required
        else:
            remove_gnd_tracks(s.pattern)
    
    def add_zone_pads(self):
        s = self.settings
        if s.pad_type == "D":
            add_front_zone_pad_D(s.pattern, corners=s.corners, outer_radius=s.pad_radius,
                    inner_radius=s.gap_center_radius, gap=s.gap_width,
                    zone_clearance=s.zone_clearance, zone_min_width=s.zone_min_width)
        else:
            add_front_zone_pads(s.pattern, corners=s.corners, outer_radius=s.pad_radius, 
                    inner_radius=s.gap_center_radius, gap=s.gap_width,
                    zone_clearance=s.zone_clearance, zone_min_width=s.zone_min_width)
    
    def remove_zone_pads(self):
        s = self.settings
        # todo, no need to specify layer, should be the same with the modules
        remove_front_zone_pads(s.pattern, corners=s.corners*2+2)
    
    def add_front_keepout(self):
        s = self.settings
        if s.pad_type == "D":
            pass
        else:
            add_front_keepout(s.pattern, corners=s.corners, outer_radius=s.outer_radius, 
                    inner_radius=s.pad_radius, gap=s.gap_width)
    
    def remove_front_keepout(self):
        s = self.settings
        # todo, without layer specified
        if s.pad_type == "D":
            pass
        else:
            remove_front_keepout(s.pattern, corners=s.corners*2+2+2)
    
    def add_back_keepout(self):
        s = self.settings
        if s.pad_type in ("A", "C"):
            add_back_keepout_A(s.pattern, corners=s.corners, outer_radius=s.outer_radius, 
                            gap=s.gap_width, no_tracks=False)
        else:
            add_back_keepout(s.pattern, corners=s.corners, radius=s.outer_radius, 
                            no_tracks=False)
    
    def remove_back_keepout(self):
        s = self.settings
        corners = s.corners
        if s.pad_type in ("A", "C"):
            corners = corners + 1 + 2
        remove_back_keepout(s.pattern, corners=corners)
    
    def add_all(self):
        self.add_gnd_track()
        self.add_zone_pads()
        self.add_front_keepout()
        self.add_back_keepout()
    
    def remove_all(self):
        self.remove_gnd_track()
        self.remove_zone_pads()
        self.remove_front_keepout()
        self.remove_back_keepout()


import wx

class ESCPToolDialog(wx.Dialog):
    
    ADD_GND_TRACK, REMOVE_GND_TRACK = 1010, 1011
    ADD_ZONE_PADS, REMOVE_ZONE_PADS = 1020, 1021
    ADD_FRONT_KEEPOUT, REMOVE_FRONT_KEEPOUT = 1030, 1031
    ADD_BACK_KEEPOUT, REMOVE_BACK_KEEPOUT = 1040, 1041
    ADD_ALL, REMOVE_ALL = 1100, 1101
    LOAD, STORE = 2011, 2012
    PAD_TYPES = "A", "B", "C", "D"
    
    class Settings:
        def __init__(self, settings):
            self.__dict__.update(settings)
    
    def __init__(self, parent, model):
        wx.Dialog.__init__(self, parent, id=wx.ID_ANY, title = u"ESCP Tool", 
                            pos=wx.DefaultPosition, size=wx.Size(-1,-1), 
                            style=wx.DEFAULT_DIALOG_STYLE)
        self.SetSizeHintsSz(wx.DefaultSize, wx.DefaultSize)
        self.Bind(wx.EVT_CLOSE, self.OnClose)
        
        self.model = model
        
        bSizer1 = wx.BoxSizer(wx.VERTICAL)
        self.commands = {}
        self.buttons = []
        
        bSizer1.Add(wx.StaticText(self, wx.ID_ANY, u"Settings"), 0, wx.LEFT | wx.TOP, 5)
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        bSizer1.Add(sizer, 0, wx.ALL, 5)
        for id, method, title in (
                    (self.LOAD, self.load_settings, u"Load"),
                    (self.STORE, self.store_settings, u"Store"),
                ):
            btn = wx.Button(self, id, title, wx.DefaultPosition, wx.DefaultSize, 0)
            sizer.Add(btn, 0, wx.ALL, 2)
            btn.Bind(wx.EVT_BUTTON, self.OnButtonClick)
            self.buttons.append(btn)
            self.commands[id] = method
        
        sizer = wx.GridSizer(1 + 7, 2)
        sizer.Add(wx.StaticText(self, wx.ID_ANY, u"Pad type"), 0, wx.LEFT, 5)
        self.type_choice = wx.Choice(self, wx.ID_ANY, choices=self.PAD_TYPES, 
                                    style=wx.CB_READONLY | wx.CB_DROPDOWN)
        self.type_choice.Select(0)
        sizer.Add(self.type_choice)
        bSizer1.Add(sizer, 0, wx.ALL, 5)
        
        self.text_controls = {}
        for name, value, label, desc in (
                    ("pattern", "SW\d*", "Reference pattern", 
                        "Matching pattern to reference for modules in regular expression."),
                    ("outer_radius", 6.5, "Outer radius", 
                        "Outer radius of pads."),
                    ("pad_radius", 5.5, "Pad Radius", 
                        "Outer radius of pads for TX/RX."),
                    ("gap_width", 0.4, "Gap width", 
                        "Width between TX and RX pads."),
                    ("gap_center_width", 0.25, "Gap center width", 
                        "Thinner gap for type A pad."),
                    ("gap_center_radius", 1.25, "Gap center radius", 
                        "Radius of center pad or empty zone."),
                    ("corners", 64, "Corners", 
                        "Number of corners for arc or circle zone."),
                    ("zone_clearance", 0.2, "Zone Clearance",
                        "Clearance for zone"),
                    ("zone_min_width", 0.2, "Zone minimum width",
                        "Minimum width of zone fill"),
                    
                ):
            text = wx.StaticText(self, wx.ID_ANY, label)
            text.SetToolTipString(desc)
            sizer.Add(text, 0, wx.ALL, 5)
            ctrl = wx.TextCtrl(self, wx.ID_ANY, "")
            ctrl.SetValue(str(value))
            ctrl.SetToolTipString(desc)
            sizer.Add(ctrl)
            self.text_controls[name] = ctrl
            
        def add_button(sizer, id, method, title):
            btn = wx.Button(self, id, title, wx.DefaultPosition, wx.DefaultSize, 0)
            sizer.Add(btn, 0, wx.ALL, 2)
            btn.Bind(wx.EVT_BUTTON, self.OnButtonClick)
            self.buttons.append(btn)
            self.commands[id] = method
        
        for title, add_id, add_method, remove_id, remove_method in (
                    (u"GND tracks", self.ADD_GND_TRACK, "add_gnd_track",
                                    self.REMOVE_GND_TRACK, "remove_gnd_track"),
                    (u"Zone pads", self.ADD_ZONE_PADS, "add_zone_pads", 
                                  self.REMOVE_ZONE_PADS, "remove_zone_pads"),
                    (u"Front keepout", self.ADD_FRONT_KEEPOUT, "add_front_keepout", 
                                      self.REMOVE_FRONT_KEEPOUT, "remove_front_keepout"),
                    (u"Back keepout", self.ADD_BACK_KEEPOUT, "add_back_keepout", 
                                     self.REMOVE_BACK_KEEPOUT, "remove_back_keepout"),
                    (u"All", self.ADD_ALL, "add_all", 
                            self.REMOVE_ALL, "remove_all"),
                ):
            bSizer1.Add(wx.StaticLine(self), flag=wx.GROW)
            bSizer1.Add(wx.StaticText(self, wx.ID_ANY, title), 0, wx.LEFT, 5)
            bSizer1.Add(wx.Panel(self, wx.ID_ANY))
            sizer = wx.BoxSizer(wx.HORIZONTAL)
            bSizer1.Add(sizer, 0, wx.ALL, 5)
            add_button(sizer, add_id, add_method, u"Add")
            add_button(sizer, remove_id, remove_method, u"Remove")
        
        self.SetSizer(bSizer1)
        self.Layout()
        self.Centre(wx.BOTH)
        bSizer1.Fit(self)
        
        # update default value from default
        self.set_settings(DEFAULT_SETTINGS)
    
    def __del__(self):
        self.model = None
    
    def OnClose(self, event):
        self.Destroy()
    
    def OnButtonClick(self, event):
        # update settings
        settings = self.get_settings()
        if settings is None:
            return
        self.model.set_settings(self.Settings(settings))
        try:
            value = self.commands[event.Id]
            if callable(value):
                value()
            else:
                getattr(self.model, value)()
        except:
            wx.MessageBox(traceback.format_exc(), "Error")
    
    def get_settings(self):
        settings = DEFAULT_SETTINGS.copy()
        del settings["pad_type"]
        try:
            for key in settings.keys():
                value = self.text_controls[key].GetValue()
                if key in ("pad_type", "pattern"):
                    pass
                elif key in ("corners",):
                    value = int(value)
                else:
                    value = float(value)
                settings[key] = value
            settings["pad_type"] = self.PAD_TYPES[self.type_choice.GetCurrentSelection()]
        except Exception as e:
            wx.MessageBox("{} should be floating point value or integer.".format(str(e)), "Error")
            traceback.print_exc()
            settings = None
        return settings
    
    def set_settings(self, settings):
        for key, value in settings.items():
            ctrl = self.text_controls.get(key, None)
            if ctrl:
                ctrl.SetValue(str(value))
    
    def load_settings(self):
        path = self.get_path(store=False)
        if path is None:
            return
        import json
        with open(path, "r") as f:
            try:
                settings = json.load(f)
            except:
                wx.MessageBox("{} file has been broken.".format(path), "Error")
                return
        self.set_settings(settings)
    
    def store_settings(self):
        settings = self.get_settings()
        if settings is None:
            return
        import json
        try:
            text = json.dumps(settings)
        except Exception as e:
            wx.MessageBox(str(e), "Error") # should not happen
            return
        path = self.get_path(store=True)
        if path is None:
            return
        with open(path, "w") as f:
            f.write(text)
    
    def get_path(self, store=False):
        flags = wx.FD_SAVE | wx.FD_OVERWRITE_PROMPT if store else wx.FD_OPEN | wx.FD_FILE_MUST_EXIST
        d = wx.FileDialog(self, "Save file" if store else "Open file", "", "",
                "JSON files (*.json)|*.json", flags)
        if d.ShowModal() == wx.ID_CANCEL:
            return None
        return d.GetPath()


# default value
DEFAULT_SETTINGS = {
    "pad_type": "A",
    "pattern": "SW\d*",
    "outer_radius": 6.5,
    "pad_radius": 5.5,
    "gap_width": 0.4,
    #"gap_width": 1.8, # D with 0.254 mm trace
    "gap_center_width": 0.25, # for A
    "gap_center_radius": 1.25,
    #"gap_center_radius": 2.8, # D
    "corners": 64,
    "zone_clearance": 0.2,
    "zone_min_width": 0.2,
}

d = locals()
for key, value in DEFAULT_SETTINGS.items():
    d[key] = value
del d

#add_gnd_tracks(pattern, width=gap_width)
#remove_gnd_tracks(pattern)

#add_front_zone_pads(pattern, corners=corners, outer_radius=pad_radius, inner_radius=gap_center_radius, gap=gap_width)
#remove_front_zone_pads(pattern, corners=corners*2+2)

#add_front_keepout(pattern, corners=corners, outer_radius=outer_radius, inner_radius=pad_radius, gap=gap_width)
#remove_front_keepout(pattern, corners=corners*2+2)

#add_back_keepout(pattern, corners=corners, radius=outer_radius)
#remove_back_keepout(pattern, corners=corners)

# show GUI panel
ESCPToolDialog(None, Model()).Show()
