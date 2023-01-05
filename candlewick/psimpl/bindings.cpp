#include <vector>

#include "pybind11/detail/common.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "psimpl.h"

namespace psimpl2d {
    using Coords = std::vector<double>;

    Coords simplify_nth_point(const Coords& coords, unsigned n) {
        Coords rv(coords.size());
        auto end = psimpl::simplify_nth_point<2>(coords.begin(), coords.end(), n, rv.begin());
        rv.erase(end, rv.end());
        return rv;
    }

    Coords simplify_radial_distance(Coords& coords, double tol) {
        Coords rv(coords.size());
        auto end = psimpl::simplify_radial_distance<2>(coords.begin(), coords.end(), tol, rv.begin());
        rv.erase(end, rv.end());
        return rv;
    }

    Coords simplify_perpendicular_distance(Coords& coords, double tol, unsigned repeat) {
        Coords rv(coords.size());
        auto end = psimpl::simplify_perpendicular_distance<2>(coords.begin(), coords.end(), tol, repeat, rv.begin());
        rv.erase(end, rv.end());
        return rv;
    }

    Coords simplify_reumann_witkam(Coords& coords, double tol) {
        Coords rv(coords.size());
        auto end = psimpl::simplify_reumann_witkam<2>(coords.begin(), coords.end(), tol, rv.begin());
        rv.erase(end, rv.end());
        return rv;
    }

    std::vector<double> simplify_opheim(std::vector<double>& coords, double min_tol, double max_tol) {
        Coords rv(coords.size());
        auto end = psimpl::simplify_opheim<2>(coords.begin(), coords.end(), min_tol, max_tol, rv.begin());
        rv.erase(end, rv.end());
        return rv;
    }

    std::vector<double> simplify_lang(std::vector<double>& coords, double tol, unsigned look_ahead) {
        Coords rv(coords.size());
        auto end = psimpl::simplify_lang<2>(coords.begin(), coords.end(), tol, look_ahead, rv.begin());
        rv.erase(end, rv.end());
        return rv;
    }

    std::vector<double> simplify_douglas_peucker(std::vector<double>& coords, double tol) {
        Coords rv(coords.size());
        auto end = psimpl::simplify_douglas_peucker<2>(coords.begin(), coords.end(), tol, rv.begin());
        rv.erase(end, rv.end());
        return rv;
    }

    std::vector<double> simplify_douglas_peucker_n(std::vector<double>& coords, unsigned count) {
        Coords rv(coords.size());
        auto end = psimpl::simplify_douglas_peucker_n<2>(coords.begin(), coords.end(), count, rv.begin());
        rv.erase(end, rv.end());
        return rv;
    }
}

namespace py = pybind11;

PYBIND11_MODULE(_psimpl, m) {

    m.def("simplify_nth_point",
          &psimpl2d::simplify_nth_point,
          py::arg("coords"),
          py::kw_only(),
          py::arg("n"),

          py::return_value_policy::move);

    m.def("simplify_radial_distance",
          &psimpl2d::simplify_radial_distance,
          py::arg("coords"),
          py::kw_only(),
          py::arg("tol"),
          py::return_value_policy::move);

    m.def("simplify_perpendicular_distance",
         &psimpl2d::simplify_perpendicular_distance,
         py::arg("coords"),
         py::kw_only(),
         py::arg("tol"),
         py::arg("n_repeat"),
         py::return_value_policy::move);

    m.def("simplify_reumann_witkam",
          &psimpl2d::simplify_reumann_witkam,
          py::arg("coords"),
          py::kw_only(),
          py::arg("tol"),
          py::return_value_policy::move);

    m.def("simplify_opheim",
          &psimpl2d::simplify_opheim,
          py::arg("coords"),
          py::kw_only(),
          py::arg("min_tol"),
          py::arg("max_tol"),
          py::return_value_policy::move);

    m.def("simplify_lang",
          &psimpl2d::simplify_lang,
          py::arg("coords"),
          py::kw_only(),
          py::arg("tol"),
          py::arg("look_ahead"),
          py::return_value_policy::move);

    m.def("simplify_douglas_peucker",
          &psimpl2d::simplify_douglas_peucker,
          py::arg("coords"),
          py::kw_only(),
          py::arg("tol"),
          py::return_value_policy::move);

    m.def("simplify_douglas_peucker_n",
          &psimpl2d::simplify_douglas_peucker_n,
          py::arg("coords"),
          py::kw_only(),
          py::arg("count"),
          py::return_value_policy::move);
}
