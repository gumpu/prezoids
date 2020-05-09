#!/usr/bin/env python
"""machine
This is machine, a bare bones state machine generator for C++

Usage:
    machine [options] <state_machine_spec> <output_file>

Options:
    -d                   show debug information
"""

from docopt import docopt
import re

class State(object):
    """Represents a state and gives access to all the transitions
    from this state to itself or other states.
    """
    def __init__(self, state_name):
        self.name = state_name
        self.transitions = []

    def add_transition(self, transition):
        self.transitions.append(transition)

    def __str__(self):
        out = "State {} ".format(self.name) + str(self.transitions)
        return out

class Event(object):
    """Represent a single event"""
    def __init__(self, event_name, parameters):
        self.name = event_name
        self.parameters = parameters

    def __str__(self):
        out = "Event " + str(self.name)
        return out

class Transition(object):
    """Represents a transition from a state to another state
    as a consequence of an event happening
    """

    def __init__(self, from_state, event, to_state):
        self.from_state = from_state # Reference to a state
        self.event      = event
        self.to_state   = to_state   # Reference to a state
    def __str__(self):
        out = "Transition( " + self.from_state.name + "->{" + self.event.name + "}->" + self.to_state.name + " )"
        return out



class Machine(object):
    """Root to all information about the state machine.
    """
    def __init__(self):
        self.name = ""
        self.states = {} # state name -> state
        self.events = [] # all events
        self.transitions = [] # all transitions
        self.event_noprint = False
        self.state_noprint = False
        #self.make_unknown_event = False
        #self.make_unknown_state = False

    def add_state(self, state):
        if state.name in self.states:
            print("State {} is already defined.".format(state.name))
            exit(1)
        else:
            self.states[state.name] = state

    def get_event(self, event_name):
        for event in self.events:
            if event.name == event_name:
                return event
        print("No such event {}".format(event_name))
        exit(1)

    def get_state(self, state_name):
        if state_name in self.states:
            return self.states[state_name]
        else:
            print("No such state {}".format(state_name))
            exit(1)

    def add_event(self, new_event):
        for event in self.events:
            if new_event.name == event.name:
                print("Event {} is already defined.".format(event.name))
                exit(1)
        self.events.append(new_event)

    def add_transition(self, from_state, transition):
        self.transitions.append(transition)
        from_state.add_transition(transition)


    def get_transitions_via_event(self, event_name):
        transitions = []
        for t in self.transitions:
            if t.event.name == event_name:
                transitions.append(t)
        return transitions

    def __str__(self):
        out = "Statemachine {}".format(self.name)
        out = out + "\n"
        #out = out + str(self.events)
        #out = out + "\n"
        #out = out + str(self.states)
        #out = out + "\n"
        transitions = "\n".join([str(x) for x in self.transitions])
        out = out + transitions
        return out

# ======================== Parser
#
def parse_line(scan, parse_state, current_state, line, verbose, machine):
    # Skip remarks and empty lines
    m = re.match("#", line)
    if m or line == "":
        if verbose:
            print("Empty of remark")
        if parse_state != "find name":
            parse_state = "find event or state"
        return parse_state, current_state

    if parse_state == "find name":
        # machine <machine name> env <environment name> [# remark]
        m = re.match(
                '^machine\s+([A-Za-z0-9_]+)\s+env\s+([A-Za-z0-9_]+)\s*($|#)',
                line)
        if m:
            if scan == 0:
                machine.name = m.group(1)
                machine.env_name = m.group(2)
                if verbose:
                    print("Machine is called {}".format(machine.name))
            parse_state = "find event or state"
            return parse_state, current_state
        else:
            print("Line: '{}'".format(line))
            print("Expected 'machine <machine name> env <environment name>'")
            print("Stopping")
            exit(1)

    # event <event name>  [# remark]
    m = re.match('^event\s+([A-Za-z0-9_]+)\s*($|#)', line)
    parameters = "yyy"
    if m is None:
        m = re.match('^event\s+([A-Za-z0-9_]+)\s+([yn]+)\s*($|#)', line)
        if m:
            parameters = m.group(2)

    if m:
        if scan == 0:
            event = Event(m.group(1), parameters)
            machine.add_event(event)
            if verbose:
                print("Event {}".format(event.name))
        parse_state = "find event or state"
        return parse_state, current_state

    # Check if print functions for event enums should be generated
    m = re.match("^enum\s+event\s+noprint", line)
    if m:
        machine.event_noprint = True
        parse_state = "find event or state"
        return parse_state, current_state
    else:
        m = re.match("^enum\s+event", line)
        if m:
            machine.event_noprint = False
            parse_state = "find event or state"
            return parse_state, current_state


    # Check if print functions for state enums should be generated
    m = re.match("^enum\s+state\s+noprint", line)
    if m:
        machine.state_noprint = True
        parse_state = "find event or state"
        return parse_state, current_state
    else:
        m = re.match("^enum\s+state", line)
        if m:
            machine.state_noprint = False
            parse_state = "find event or state"
            return parse_state, current_state

    # state <state name> [# remark]
    m = re.match("^state\s+([A-Za-z0-9_]+)", line)
    if m:
        state_name = m.group(1)
        parse_state = "find transition"
        if scan == 0:
            state = State(state_name)
            machine.add_state(state)
            if verbose:
                print("Found state {}".format(state.name))
            parse_state = "find transition"
            return parse_state, current_state
        else:
            current_state = machine.get_state(state_name)
            return parse_state, current_state

    # <event name> -> <to state>
    m = re.match("^([A-Za-z0-9_]+)\s+->\s+([A-Za-z0-9_]+)", line)
    if m and parse_state == "find transition":
        if scan == 1:
            event_name = m.group(1)
            state_name = m.group(2)
            event = machine.get_event(event_name)
            to_state = machine.get_state(state_name)
            if scan == 1:
                transition = Transition(current_state, event, to_state)
                machine.add_transition(current_state, transition)
                if verbose:
                    print("Found transition for {}".format(
                        current_state.name))
        return parse_state, current_state
    else:
        if m:
            print("Found a transition outside a state.")
        else:
            print("Can't parse '{}'".format(line))
            exit(1)

    return parse_state, current_state

def parse(filename, verbose):
    machine = Machine()
    # Have to scan 2 times because transitions for a state
    # might refer to a state further down in the specification
    for scan in range(2):
        current_state = None
        parse_state = "find name"
        with open(filename, "r") as inpf:
            for line in inpf:
                line = line.strip()
                if verbose:
                    print("Pass {} {} '{}'".format(parse_state, scan, line))
                parse_state, current_state = parse_line(
                        scan, parse_state, current_state,
                        line, verbose, machine)

    if verbose:
        print("Done parsing")
    return machine

# ============================================================================

def emit_code(code_file, indent, code, full_line=True):
    """Emit a single line of code with a given indentation"""
    code_file.write(" "*indent)
    code_file.write(code)
    if full_line:
        code_file.write("\n")

def gen_header(header_filename):
    # TODO
    pass

def gen_implementation(header_filename):
    # TODO
    pass

def generate(filename):
    basename = re.sub("\.cpp$", "", filename)
    print("Basename: {}".format(basename))
    header_filename = basename + ".h"
    implementation_filename = basename + ".cpp"
    print("Header: {}".format(header_filename))
    print("Implementation: {}".format(implementation_filename))

# ============================================================================

if __name__ == "__main__":
    arguments = docopt(__doc__, version='machine 0.0.1')

    input_filename = arguments['<state_machine_spec>']
    output_filename = arguments['<output_file>']
    machine = parse(input_filename, arguments['-d'])
    print(machine)
    generate(output_filename)

# --------------- end of file -----------------------------------------
