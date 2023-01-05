"""
Polylines/polygons simplification module
"""

from __future__ import annotations
from itertools import chain
from typing import Iterable, Callable, List, TypeVar, Tuple

from shapely.geometry import LineString, Polygon

from .psimpl import *

T_ = TypeVar("T_")


def _pairwise(xs: List[T_]) -> List[Tuple[T_, T_]]:
    it = iter(xs)
    return list(zip(it, it))


def _linearize(xs: Iterable[Iterable[T_]]) -> List[T_]:
    return list(chain.from_iterable(xs))


def _get_algorithm(algorithm: str):
    algorithm = algorithm.lower()
    if algorithm in ['rdp', 'douglas-peucker']:
        return simplify_douglas_peucker
    elif algorithm == 'nth':
        return simplify_nth_point
    elif algorithm == 'radial':
        return simplify_radial_distance
    elif algorithm in ['pd', 'perpendicular']:
        return simplify_perpendicular_distance
    elif algorithm in ['rw', 'reumann-witkam']:
        return simplify_reumann_witkam
    elif algorithm == 'opheim':
        return simplify_opheim
    elif algorithm == 'lang':
        return simplify_opheim
    elif algorithm == 'raposo':
        return ...
    elif algorithm in ['lo', 'li-openshaw']:
        return ...
    else:
        return ValueError('Unknown simplification algorithm')


def _simplify_line(obj, algorithm, params):
    type_obj = type(obj)
    if isinstance(obj, LineString):
        obj = list(obj.coords)

    coords = _linearize(obj)
    coords = _get_algorithm(algorithm)(coords, **params)
    coords = _pairwise(coords)

    return type_obj(coords)


def _simplify_polygon(obj, algorithm, params):
    algorithm_impl = _get_algorithm(algorithm)

    coords_fst = _linearize(obj.boundary.coords)[:-2]
    stage_fst = algorithm_impl(coords_fst, **params)

    k = len(stage_fst) // 2 - (len(stage_fst) // 2 % 2)
    coords_snd = stage_fst[k:]
    coords_snd += stage_fst[:k]
    stage_snd = algorithm_impl(coords_snd, **params)

    coords = _pairwise(stage_snd)

    return Polygon(coords)


def simplify(obj: Iterable | LineString | Polygon, *, algorithm: str = 'rdp', **params):
    if isinstance(obj, Polygon):
        simplified = _simplify_polygon(obj, algorithm, params)
    else:
        simplified = _simplify_line(obj, algorithm, params)

    return simplified
