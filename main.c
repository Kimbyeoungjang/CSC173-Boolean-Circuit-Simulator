/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Tue Jul 17 16:02:29 EDT 2018 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* and3_Circuit() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* A1 = new_AndGate();
	Gate* A2 = new_AndGate();
	Gate** gates = new_Gate_array(2);
	gates[0] = A1;
	gates[1] = A2;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 2, gates);
	Circuit_connect(circuit, x, Gate_getInput(A1, 0));
	Circuit_connect(circuit, y, Gate_getInput(A1, 1));
	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(A2, 0));
	Circuit_connect(circuit, z, Gate_getInput(A2, 1));
	Circuit_connect(circuit, Gate_getOutput(A2), out);
	return circuit;
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

static Circuit* circuit2_Test() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(2);
	inputs[0] = x;
	inputs[1] = y;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* A1 = new_NandGate();
	Gate* A2 = new_OrGate();
	Gate* A3 = new_AndGate();
	Gate** gates = new_Gate_array(3);
	gates[0] = A1;
	gates[1] = A2;
	gates[2] = A3;

	Circuit *circuit = new_Circuit(2, inputs, 1, outputs, 3, gates);

	Circuit_connect(circuit, x, Gate_getInput(A1, 0));
	Circuit_connect(circuit, x, Gate_getInput(A2, 0));

	Circuit_connect(circuit, y, Gate_getInput(A1, 1));
	Circuit_connect(circuit, y, Gate_getInput(A2, 1));

	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(A3, 0));
	Circuit_connect(circuit, Gate_getOutput(A2), Gate_getInput(A3, 1));

	Circuit_connect(circuit, Gate_getOutput(A3), out);

	return circuit;
}

static void testCircuit2(Circuit* circuit, bool in0, bool in1) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	
	Circuit_update(circuit);
	
	bool out0 = Circuit_getOutput(circuit, 0);
	
	printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}

int main(int argc, char **argv) {
	Circuit* circuit = circuit2_Test();

	printf("The and3 circuit (AND of three inputs):\n");
	Circuit_dump(circuit);
	printf("\n");

	printf("Testing: true true\n");
	testCircuit2(circuit, true, true);

	printf("Testing: true false\n");
	testCircuit2(circuit, true, false);

	printf("Testing: false true\n");
	testCircuit2(circuit, false, true);

	printf("Testing: false false\n");
	testCircuit2(circuit, false, false);
		
	Circuit_free(circuit);
}