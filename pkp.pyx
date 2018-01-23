from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp cimport bool

cdef extern from "reactor.hpp" namespace "pkp":
    cdef cppclass CxxReactor "pkp::Reactor":
        CxxReactor(string, vector[double])
        void solve(double dt, bool verbose)
        vector[double] getParameters()
        void setParameters(vector[double])
        vector[double] getTimes()
        vector[vector[double]] getStates()
        void dump(string csv, string sep)
        void printParameters()
        vector[vector[double]] getOperatingConditions()
        void setOperatingConditions(vector[vector[double]])



cdef class Reactor:
    cdef CxxReactor* _c_reactor
    def __cinit__(self, name, parameters):
        cdef string c_name = name.encode()
        cdef vector[double] c_parameters = parameters
        self._c_reactor = new CxxReactor(c_name, c_parameters)

    def solve(self, dt, verbose=True):
        cdef double dt_c = dt
        cdef bool verbose_c = verbose
        self._c_reactor.solve(dt_c, verbose_c)

    def _get_parameters(self):
        return self._c_reactor.getParameters()

    def _set_parameters(self, parameters):
        cdef vector[double] parameters_c = parameters
        # for p in parameters:
        #    parameters_c.push_back(p)
        self._c_reactor.setParameters(parameters_c)

    parameters = property(_get_parameters, _set_parameters)

    def _get_times(self):
        return self._c_reactor.getTimes()

    times = property(_get_times)

    def _get_states(self):
        return self._c_reactor.getStates()

    states = property(_get_states)

    def dump(self, csv, sep=','):
        cdef string csv_c = csv.encode()
        cdef sep_c = sep.encode()
        self._c_reactor.dump(csv_c, sep_c)

    def _get_operating_conditions(self):
        return self._c_reactor.getOperatingConditions()

    def _set_operating_conditions(self, oc):
        cdef vector[vector[double]] oc_c = oc
        self._c_reactor.setOperatingConditions(oc_c)

    operating_conditions = property(_get_operating_conditions, _set_operating_conditions)
