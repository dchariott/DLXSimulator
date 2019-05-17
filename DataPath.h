//
// Created by Dylan Chariott on 2019-04-24.
//

#ifndef DLXSIMULATOR_DATAPATH_H
#define DLXSIMULATOR_DATAPATH_H

#include <string>
#include "StateMachine.h"
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#define BYTE 0
#define HALF 1
#define WORD 2
using namespace std;

class DataPath{
private:
  int mainMemory[5000];
  int regFile[32];
  map<int, string> opcodes;
  map<int, string> functCodes;
  StateMachine state;
  ofstream processInfo;
  int mdr;
  int mar;
  int ir;
  int pc;
  int instrCount;
  unsigned int rs1;
  unsigned int rs2;
  unsigned int rd;
  int imm;
  int offset;
  int s1;
  int s2;
  int dest;
  int addr;
  int data;
  int a;
  int b;
  int c;
  int instruction;
  int ReadMemory(int address, int word_byte_half);
  int WriteMemory(int address, int data, int word_byte_half);
  void ResetControls();
  void Add();
  void AddI();
  void And();
  void Beqz();
  void Bnez();
  void J();
  void Lb();
  void Lh();
  void Lw();
  void Or();
  void OrI();
  void Sll();
  void Srl();
  void Sb();
  void Sh();
  void Sw();
  void Sub();
public:
  DataPath();
  int LoadProgramCode(string fileName);
  void PrintState();
  void PrintCurrentInstruction();
  void RunProgram();
};
#endif //DLXSIMULATOR_DATAPATH_H
