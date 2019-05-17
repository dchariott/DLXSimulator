//
// Created by Dylan Chariott on 2019-04-24.
//

#include "DataPath.h"

DataPath::DataPath(): state(StateMachine()){
    opcodes = {
              {2, "j"}, {3, "jal"}, {4, "beqz"}, {5, "bnez"}, {8, "addi"}, {9, "addui"}, {10, "subi"}, {11, "subui"},
              {12, "andi"}, {13, "ori"}, {14, "xori"}, {15, "lhi"}, {18, "jr"}, {19, "jalr"}, {24, "seqi"},
              {25, "snei"}, {26, "slti"}, {27, "sgti"}, {28, "slei"}, {29, "sgei"},
              {32, "lb"}, {33, "lh"}, {35, "lw"}, {36, "lbu"}, {37, "lhu"}, {40, "sb"}, {41, "sh"},
              {43, "sw"}, {48, "sequi"}, {49, "senui"}, {50, "sltui"}, {51, "sgtui"}, {52, "sleui"}, {53, "sgeui"},
              {54, "slli"}, {55, "srli"}, {56, "srai"}
             };
    functCodes = {
                 {4, "sll"}, {6, "srl"}, {7, "sra"}, {18, "sltu"}, {19, "sgtu"}, {20, "sleu"},
                 {21, "sgeu"}, {32, "add"}, {33, "addu"}, {34, "sub"}, {35, "subu"}, {36, "and"}, {37, "or"},
                 {38, "xor"}, {40, "seq"}, {41, "sne"}, {42, "slt"}, {43, "sgt"}, {44, "sle"}, {45, "sge"}
                };
    mar = 0;
    mdr = 0;
    pc = 0;
    instrCount = 0;
    for (int i = 0; i < 32; i++){
        regFile[i] = i * 10;
    }
    processInfo.open("process.txt");
}

int DataPath::LoadProgramCode(string fileName){
    ifstream program;
    unsigned int temp = 0;
    int i = 0;
    program.open(fileName);
    if (!program.is_open()){
        return 0;
    }

    while (program >> hex >> temp){
        mainMemory[i] = temp;
        instrCount++;
        i++;
    }
    program.close();
    return 1;
}

int DataPath::ReadMemory(int address, int word_byte_half){
    if (address >= 5000){
        return 0;
    }
    int mask = 0b11111111111111111111111111111111;
    data = mainMemory[address];
    switch(word_byte_half){
        case 0:
            mask = 0b00000000000000000000000011111111;
            break;
        case 1:
            mask = 0b000000000000000011111111111111111;
            break;
    }
    data &= mask;
    return 1;
}

int DataPath::WriteMemory(int address, int data,  int word_byte_half){
    int mask = 0b11111111111111111111111111111111;
    if (address < instrCount || address >= 5000){
        return 0;
    }
    else{
        switch(word_byte_half){
            case 0:
                mask = 0b00000000000000000000000011111111;
                break;
            case 1:
                mask = 0b000000000000000011111111111111111;
                break;
        }
        mainMemory[address] = data & mask;
        return 1;
    }
}

void DataPath::PrintState(){
    cout << "Register File:" << endl;
    processInfo << "Register File:" << endl;
    for (int i = 0; i < 16; i++){
        cout << " R" << i << ": " << regFile[i];
        processInfo << " R" << i << ": " << regFile[i];
    }
    cout << endl;
    processInfo << endl;
    for (int i = 16; i < 32; i++){
        cout << " R" << i << ": " << regFile[i];
        processInfo << " R" << i << ": " << regFile[i];
    }
    cout << endl;
    processInfo << endl;
    cout << "Memory Registers: " << endl
         << " MDR: " << mdr << " MAR: " << mar << endl;
    cout << "Hardware Registers: " << endl
         << " IR: " << ir << " PC: " << pc << endl;
    cout << "Data Bus: " << endl
         << " S1: " << s1 << " S2: " << s2 << " Dest: " << dest << " Addr: " << addr << " Data: " << data << endl;
    cout << "Register Buffers: " << endl
         << " A: " << a << " B: " << b << " C: " << c << endl;
    cout << "Control Signals:" << endl
         << " S2op: " << state.GetS2op() << " ALUop: " << state.GetALUop() << " Cload: " << state.GetCload()
         << " REGload: " << state.GetREGload() << " REGselect: " << state.GetREGselect() << " Aload: " << state.GetAload()
         << " Aoe: " << state.GetAoe() << " Bload: " << state.GetBload() << " Boe: " << state.GetBoe()
         << " IRload: " << state.GetIRload() << endl <<" IRoeS1: " << state.GetIRoeS1() << " IRoeS2: " << state.GetIRoeS2()
         << " Reset: " << state.GetReset() << " PCload: " << state.GetPCload() << " PCoeS1: " << state.GetPCoeS1()
         << " PCMARselect: " << state.GetPCMARselect() << " MARload: " << state.GetMARload() << " MDRload: "
         << state.GetMDRload() << " MDRoeS2: " << state.GetMDRoeS2() << " MemRead: " << state.GetMemRead()
         << " MemWrite: " << state.GetMemWrite() << " MemOp: " << state.GetMemOp() << endl;
    processInfo << "Memory Registers: " << endl
         << " MDR: " << mdr << " MAR: " << mar << endl;
    processInfo << "Hardware Registers: " << endl
         << " IR: " << ir << " PC: " << pc << endl;
    processInfo << "Data Bus: " << endl
         << " S1: " << s1 << " S2: " << s2 << " Dest: " << dest << " Addr: " << addr << " Data: " << data << endl;
    processInfo << "Register Buffers: " << endl
         << " A: " << a << " B: " << b << " C: " << c << endl;
    processInfo << "Control Signals:" << endl
         << " S2op: " << state.GetS2op() << " ALUop: " << state.GetALUop() << " Cload: " << state.GetCload()
         << " REGload: " << state.GetREGload() << " REGselect: " << state.GetREGselect() << " Aload: " << state.GetAload()
         << " Aoe: " << state.GetAoe() << " Bload: " << state.GetBload() << " Boe: " << state.GetBoe()
         << " IRload: " << state.GetIRload() << endl <<" IRoeS1: " << state.GetIRoeS1() << " IRoeS2: " << state.GetIRoeS2()
         << " Reset: " << state.GetReset() << " PCload: " << state.GetPCload() << " PCoeS1: " << state.GetPCoeS1()
         << " PCMARselect: " << state.GetPCMARselect() << " MARload: " << state.GetMARload() << " MDRload: "
         << state.GetMDRload() << " MDRoeS2: " << state.GetMDRoeS2() << " MemRead: " << state.GetMemRead()
         << " MemWrite: " << state.GetMemWrite() << " MemOp: " << state.GetMemOp() << endl;
}

void DataPath::ResetControls(){
    state.SetMemRead(0);
    state.SetIRload(0);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetS2op(0);
    state.SetPCload(0);
    state.SetALUop(0);
    state.SetMemOp(0);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    state.SetREGload(0);
    state.SetREGselect(0);
    state.SetIRoeS1(0);
    state.SetIRoeS2(0);
    state.SetReset(0);
    state.SetPCMARSelect(0);
    state.SetMARload(0);
    state.SetMemWrite(0);
    state.SetMDRload(0);
    state.SetMDRoeS2(0);
}

void DataPath::PrintCurrentInstruction(){
    int opcodeMask = 0b11111100000000000000000000000000;
    unsigned int opcode = instruction & opcodeMask;
    opcode >>= 26;
    string operation;
    cout << "Current Instruction: " << endl;
    processInfo << "Current Instruction: " << endl;
    if (opcode == 0){
        int functCodeMask = 0b00000000000000000000011111111111;
        int functCode = instruction & functCodeMask;
        operation = functCodes.at(functCode);
        int rs1Mask = 0b00000011111000000000000000000000;
        rs1 = (instruction & rs1Mask) >> 21;
        int rs2Mask = 0b00000000000111110000000000000000;
        rs2 = (instruction & rs2Mask) >> 16;
        int rdMask = 0b00000000000000001111100000000000;
        rd = (instruction & rdMask) >> 11;
    }
    else if (opcode == 2 || opcode == 3){
        int offsetMask = 0b0000001111111111111111111111111;
        offset = instruction & offsetMask;
        operation = opcodes.at(opcode);
    }
    else{
        operation = opcodes.at(opcode);
        int rs1Mask = 0b00000011111000000000000000000000;
        rs1 = (instruction & rs1Mask) >> 21;
        int rs2Mask = 0b00000000000111110000000000000000;
        rs2 = (instruction & rs2Mask) >> 16;
        int immMask = 0b00000000000000001111111111111111;
        imm = (instruction & immMask) >> 11;
    }

    if (opcode == 0){
        cout << operation << " r" << rd << ", r" << rs1 << ", r" << rs2 << endl;
        processInfo << operation << " r" << rd << ", r" << rs1 << ", r" << rs2 << endl;
    }
    else if (operation.find('j') == 0){
        cout << operation << " " << offset << endl;
        processInfo << operation << " " << offset << endl;
    }
    else if (operation.find('b') == 0){
        cout << operation << " r" << rs1 << ", " << imm << endl;
        processInfo << operation << " r" << rs1 << ", " << imm << endl;
    }
    else if (operation.find('l') == 0){
        cout << operation << " r" << rs2 << ", " << imm << "(r" << rs1 << ")" << endl;
        processInfo << operation << " r" << rs2 << ", " << imm << "(r" << rs1 << ")" << endl;
    }
    else if (operation.find('s') == 0){
        cout << operation << " " << imm << "(r" << rs1 << "), r" << rs2 << endl;
        processInfo << operation << " " << imm << "(r" << rs1 << "), r" << rs2 << endl;
    }
    else{
        cout << operation << " r" << rs2 << ", r" << rs1 << ", " << imm << endl;
        processInfo << operation << " r" << rs2 << ", r" << rs1 << ", " << imm << endl;
    }
}

void DataPath::RunProgram(){
    while ((pc/4) < instrCount){
        cout << "Instruction " << pc/4 + 1 << ": " << endl;
        processInfo << "Instruction " << pc/4 + 1 << ": " << endl;
        cout << "Step 1 (Fetching Instruction): " << endl;
        processInfo << "Step 1 (Fetching Instruction): " << endl;
        state.SetIRload(1);
        state.SetMemRead(1);
        state.SetMemOp(0);
        state.SetPCMARSelect(0);
        addr = pc;
        instruction = mainMemory[pc/4];
        data = instruction;
        ir = instruction;
        PrintState();
        PrintCurrentInstruction();
        string operation;
        int opcodeMask = 0b11111100000000000000000000000000;
        unsigned int opcode = instruction & opcodeMask;
        opcode >>= 26;
        if (opcode == 0){
            int functCodeMask = 0b00000000000000000000011111111111;
            int functCode = instruction & functCodeMask;
            operation = functCodes.at(functCode);
        }
        else{
            operation = opcodes.at(opcode);
        }
        cout << "Step 2 (Loading A and B and Update PC): " << endl;
        processInfo << "Step 2 (Loading A and B and Update PC): " << endl;
        state.SetMemRead(0);
        state.SetIRload(0);
        state.SetAload(1);
        state.SetBload(1);
        state.SetPCoeS1(1);
        state.SetS2op(7);
        state.SetPCload(1);
        state.SetALUop(0);
        s1 = pc;
        s2 = 4;
        pc += 4;
        dest = s1 + s2;
        a = regFile[rs1];
        b = regFile[rs2];
        PrintState();

        if (operation == "add"){
            Add();
        }
        else if (operation == "addi"){
            AddI();
        }
        else if (operation == "and"){
            And();
        }
        else if (operation == "beqz"){
            Beqz();
        }
        else if (operation == "bnez"){
            Bnez();
        }
        else if (operation == "j"){
            J();
        }
        else if (operation == "lb"){
            Lb();
        }
        else if (operation == "lh"){
            Lh();
        }
        else if (operation == "lw"){
            Lw();
        }
        else if (operation == "or"){
            Or();
        }
        else if (operation == "ori"){
            OrI();
        }
        else if (operation == "sll"){
            Sll();
        }
        else if (operation == "srl"){
            Srl();
        }
        else if (operation == "sb"){
            Sb();
        }
        else if (operation == "sh"){
            Sh();
        }
        else if (operation == "sw"){
            Sw();
        }
        else if (operation == "sub"){
            Sub();
        }
        else{
            cout << "Unsupported Operation" << endl;
            processInfo << "Unsupported Operation" << endl;
        }
        cout << endl;
        processInfo << endl;
        ResetControls();
    }
}

void DataPath::Add(){
    cout << "Step 3 (Add A and B, Save to C): " << endl;
    processInfo << "Step 3 (Add A and B, Save to C): " << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(0);
    state.SetCload(1);
    state.SetS2op(0);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = b;
    dest = a + b;
    c = dest;
    PrintState();
    cout << "Step 4 (Save C to rd):" << endl;
    processInfo << "Step 4 (Save C to rd):" << endl;
    state.SetREGload(1);
    state.SetREGselect(0);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    regFile[rd] = c;
    PrintState();
 }

 void DataPath::AddI(){
    cout << "Step 3 (Add A and Imm, Save to C):" << endl;
    processInfo << "Step 3 (Add A and Imm, Save to C):" << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(1);
    state.SetIRoeS2(1);
    state.SetS2op(3);
    state.SetCload(1);
    state.SetS2op(0);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = ir;
    dest = a + ir;
    c = dest;
    PrintState();
    cout << "Step 4 (Save C to rs2):" << endl;
    processInfo << "Step 4 (Save C to rs2):" << endl;
    state.SetREGload(1);
    state.SetREGselect(1);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    regFile[rs2] = c;
    PrintState();
}

void DataPath::And(){
    cout << "Step 3 (Compare A and B, Save to C): " << endl;
    processInfo << "Step 3 (Compare A and B, Save to C): " << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(4);
    state.SetCload(1);
    state.SetS2op(0);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = b;
    dest = a & b;
    c = dest;
    PrintState();
    cout << "Step 4 (Save C to rd):" << endl;
    processInfo << "Step 4 (Save C to rd):" << endl;
    state.SetREGload(1);
    state.SetREGselect(0);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    regFile[rd] = c;
    PrintState();
}

void DataPath::Beqz(){
    cout << "Step 3 (Compare Result and 0, Update PC if equal to 0):" << endl;
    processInfo << "Step 3 (Compare Result and 0, Update PC if equal to 0):" << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(16);
    state.SetS2op(0);
    state.SetCload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = b;
    dest = (a == b)? 1:0;
    c = dest;
    PrintState();
    if (c){
        cout << "Step 4 (Set PC to Offset):" << endl;
        processInfo << "Step 4 (Set PC to Offset):" << endl;
        state.SetAoe(0);
        state.SetBoe(0);
        state.SetCload(0);
        state.SetIRoeS2(1);
        state.SetPCoeS1(1);
        state.SetS2op(5);
        state.SetALUop(0);
        state.SetPCload(1);
        s1 = pc;
        s2 = offset;
        dest = pc + offset;
        pc = pc + offset;
        PrintState();
    }
}

void DataPath::Bnez(){
    cout << "Step 3 (Compare Result and 0, Update PC if equal to 0):" << endl;
    processInfo << "Step 3 (Compare Result and 0, Update PC if equal to 0):" << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(18);
    state.SetS2op(0);
    state.SetCload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = b;
    dest = (a != b)? 1:0;
    c = dest;
    PrintState();
    if (c){
        cout << "Step 4 (Set PC to Offset):" << endl;
        processInfo << "Step 4 (Set PC to Offset):" << endl;
        state.SetAoe(0);
        state.SetBoe(0);
        state.SetCload(0);
        state.SetIRoeS2(1);
        state.SetPCoeS1(1);
        state.SetS2op(5);
        state.SetALUop(0);
        state.SetPCload(1);
        s1 = pc;
        s2 = offset;
        dest = pc + offset;
        pc = pc + offset;
        PrintState();
    }
}

void DataPath::J(){
    cout << "Step 3 (Set PC to Offset):" << endl;
    processInfo << "Step 3 (Set PC to Offset):" << endl;
    state.SetPCoeS1(1);
    state.SetIRoeS2(1);
    state.SetS2op(5);
    state.SetALUop(0);
    state.SetIRoeS2(1);
    state.SetS2op(5);
    state.SetPCload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    s1 = pc;
    s2 = offset;
    dest = pc + offset;
    pc = pc + offset;
    PrintState();
}

void DataPath::Lb(){
    cout << "Step 3 (Add A and IR, send to MAR):" << endl;
    processInfo << "Step 3 (Add A and IR, send to MAR):" << endl;
    state.SetAoe(1);
    state.SetIRoeS2(1);
    state.SetS2op(3);
    state.SetALUop(0);
    state.SetMARload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = imm;
    dest = a + imm;
    mar = dest;
    PrintState();
    cout << "Step 4 (With MAR loaded fetch Data from MDR, save to C):" << endl;
    processInfo << "Step 4 (With MAR loaded fetch Data from MDR, save to C):" << endl;
    state.SetPCMARSelect(1);
    state.SetMemOp(2);
    state.SetMemRead(1);
    state.SetMDRload(1);
    state.SetMDRoeS2(1);
    state.SetS2op(0);
    state.SetALUop(3);
    state.SetCload(1);
    state.SetAoe(0);
    state.SetS2op(0);
    state.SetMARload(0);
    addr = mar;
    ReadMemory(mar, BYTE);
    mdr = data;
    s2 = mdr;
    dest = s2;
    c = dest;
    PrintState();
    cout << "Step 5 (Save C to rs2):" << endl;
    processInfo << "Step 5 (Save C to rs2):" << endl;
    state.SetREGload(1);
    state.SetREGselect(1);
    state.SetCload(0);
    state.SetMemOp(0);
    state.SetMemRead(0);
    state.SetMDRload(0);
    state.SetMDRoeS2(0);
    state.SetALUop(0);
    state.SetPCMARSelect(0);
    regFile[rs2] = c;
    PrintState();
}

void DataPath::Lh(){
    cout << "Step 3 (Add A and IR, send to MAR):" << endl;
    processInfo << "Step 3 (Add A and IR, send to MAR):" << endl;
    state.SetAoe(1);
    state.SetIRoeS2(1);
    state.SetS2op(3);
    state.SetALUop(0);
    state.SetMARload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = imm;
    dest = a + imm;
    mar = dest;
    PrintState();
    cout << "Step 4 (With MAR loaded fetch Data from MDR, save to C):" << endl;
    processInfo << "Step 4 (With MAR loaded fetch Data from MDR, save to C):" << endl;
    state.SetPCMARSelect(1);
    state.SetMemOp(1);
    state.SetMemRead(1);
    state.SetMDRload(1);
    state.SetMDRoeS2(1);
    state.SetS2op(0);
    state.SetALUop(3);
    state.SetCload(1);
    state.SetAoe(0);
    state.SetS2op(0);
    state.SetMARload(0);
    addr = mar;
    ReadMemory(mar, HALF);
    mdr = data;
    s2 = mdr;
    dest = s2;
    c = dest;
    PrintState();
    cout << "Step 5 (Save C to rs2):" << endl;
    processInfo << "Step 5 (Save C to rs2):" << endl;
    state.SetREGload(1);
    state.SetREGselect(1);
    state.SetCload(0);
    state.SetMemOp(0);
    state.SetMemRead(0);
    state.SetMDRload(0);
    state.SetMDRoeS2(0);
    state.SetALUop(0);
    state.SetPCMARSelect(0);
    regFile[rs2] = c;
    PrintState();
}

void DataPath::Lw(){
    cout << "Step 3 (Add A and IR, send to MAR):" << endl;
    processInfo << "Step 3 (Add A and IR, send to MAR):" << endl;
    state.SetAoe(1);
    state.SetIRoeS2(1);
    state.SetS2op(3);
    state.SetALUop(0);
    state.SetMARload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = imm;
    dest = a + imm;
    mar = dest;
    PrintState();
    cout << "Step 4 (With MAR loaded fetch Data from MDR, save to C):" << endl;
    processInfo << "Step 4 (With MAR loaded fetch Data from MDR, save to C):" << endl;
    state.SetPCMARSelect(1);
    state.SetMemOp(0);
    state.SetMemRead(1);
    state.SetMDRload(1);
    state.SetMDRoeS2(1);
    state.SetS2op(0);
    state.SetALUop(3);
    state.SetCload(1);
    state.SetAoe(0);
    state.SetS2op(0);
    state.SetMARload(0);
    addr = mar;
    ReadMemory(mar, WORD);
    mdr = data;
    s2 = mdr;
    dest = s2;
    c = dest;
    PrintState();
    cout << "Step 5 (Save C to rs2):" << endl;
    processInfo << "Step 5 (Save C to rs2):" << endl;
    state.SetREGload(1);
    state.SetREGselect(1);
    state.SetCload(0);
    state.SetMemRead(0);
    state.SetMDRload(0);
    state.SetMDRoeS2(0);
    state.SetALUop(0);
    state.SetPCMARSelect(0);
    regFile[rs2] = c;
    PrintState();
}

void DataPath::Or(){
    cout << "Step 3 (Compare A and B, Save to C): " << endl;
    processInfo << "Step 3 (Compare A and B, Save to C): " << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(5);
    state.SetCload(1);
    state.SetS2op(0);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = b;
    dest = a | b;
    c = dest;
    PrintState();
    cout << "Step 4 (Save C to rd):" << endl;
    processInfo << "Step 4 (Save C to rd):" << endl;
    state.SetREGload(1);
    state.SetREGselect(0);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    regFile[rd] = c;
    PrintState();
}

void DataPath::OrI(){
    cout << "Step 3 (Compare A and IR, Save to C): " << endl;
    processInfo << "Step 3 (Compare A and IR, Save to C): " << endl;
    state.SetAoe(1);
    state.SetIRoeS2(1);
    state.SetALUop(5);
    state.SetCload(1);
    state.SetS2op(3);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = ir;
    dest = a | ir;
    c = dest;
    PrintState();
    cout << "Step 4 (Save C to rs2):" << endl;
    processInfo << "Step 4 (Save C to rs2):" << endl;
    state.SetREGload(1);
    state.SetREGselect(1);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    regFile[rs2] = c;
    PrintState();
}

void DataPath::Sll(){
    cout << "Step 3 (Shift A logically left B times, Save to C): " << endl;
    processInfo << "Step 3 (Shift A logically left B times, Save to C): " << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(8);
    state.SetCload(1);
    state.SetS2op(0);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = b;
    dest = a << b;
    c = dest;
    PrintState();
    cout << "Step 4 (Save C to rd):" << endl;
    processInfo << "Step 4 (Save C to rd):" << endl;
    state.SetREGload(1);
    state.SetREGselect(0);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    regFile[rd] = c;
    PrintState();
}

void DataPath::Srl(){
    cout << "Step 3 (Shift A logically right B times, Save to C): " << endl;
    processInfo << "Step 3 (Shift A logically right B times, Save to C): " << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(10);
    state.SetCload(1);
    state.SetS2op(0);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = b;
    dest = a >> b;
    c = dest;
    PrintState();
    cout << "Step 4 (Save C to rd):" << endl;
    processInfo << "Step 4 (Save C to rd):" << endl;
    state.SetREGload(1);
    state.SetREGselect(0);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    regFile[rd] = c;
    PrintState();
}

void DataPath::Sb(){
    cout << "Step 3 (Add A and IR, send to MAR):" << endl;
    processInfo << "Step 3 (Add A and IR, send to MAR):" << endl;
    state.SetAoe(1);
    state.SetIRoeS2(1);
    state.SetS2op(3);
    state.SetALUop(0);
    state.SetMARload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = imm;
    dest = a + imm;
    mar = dest;
    PrintState();
    cout << "Step 4 (With MAR loaded load Data into MDR):" << endl;
    processInfo << "Step 4 (With MAR loaded load Data into MDR):" << endl;
    state.SetPCMARSelect(1);
    state.SetMDRload(1);
    state.SetBoe(1);
    state.SetS2op(0);
    state.SetALUop(3);
    state.SetAoe(0);
    state.SetS2op(0);
    state.SetMARload(0);
    addr = mar;
    s2 = b;
    data = b;
    mdr = data;
    PrintState();
    cout << "Step 5 (Write from MDR to MEM):" << endl;
    processInfo << "Step 5 (Write from MDR to MEM):" << endl;
    state.SetMemOp(2);
    state.SetMemWrite(1);
    state.SetMDRload(0);
    state.SetBoe(0);
    state.SetALUop(0);
    state.SetPCMARSelect(0);
    WriteMemory(mar, mdr, BYTE);
    PrintState();
}

void DataPath::Sh(){
    cout << "Step 3 (Add A and IR, send to MAR):" << endl;
    processInfo << "Step 3 (Add A and IR, send to MAR):" << endl;
    state.SetAoe(1);
    state.SetIRoeS2(1);
    state.SetS2op(3);
    state.SetALUop(0);
    state.SetMARload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = imm;
    dest = a + imm;
    mar = dest;
    PrintState();
    cout << "Step 4 (With MAR loaded load Data into MDR):" << endl;
    processInfo << "Step 4 (With MAR loaded load Data into MDR):" << endl;
    state.SetPCMARSelect(1);
    state.SetMDRload(1);
    state.SetBoe(1);
    state.SetS2op(0);
    state.SetALUop(3);
    state.SetAoe(0);
    state.SetS2op(0);
    state.SetMARload(0);
    addr = mar;
    s2 = b;
    data = b;
    mdr = data;
    PrintState();
    cout << "Step 5 (Write from MDR to MEM):" << endl;
    processInfo << "Step 5 (Write from MDR to MEM):" << endl;
    state.SetMemOp(1);
    state.SetMemWrite(1);
    state.SetMDRload(0);
    state.SetBoe(0);
    state.SetALUop(0);
    state.SetPCMARSelect(0);
    WriteMemory(mar, mdr, HALF);
    PrintState();
}

void DataPath::Sw(){
    cout << "Step 3 (Add A and IR, send to MAR):" << endl;
    processInfo << "Step 3 (Add A and IR, send to MAR):" << endl;
    state.SetAoe(1);
    state.SetIRoeS2(1);
    state.SetS2op(3);
    state.SetALUop(0);
    state.SetMARload(1);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = imm;
    dest = a + imm;
    mar = dest;
    PrintState();
    cout << "Step 4 (With MAR loaded load Data into MDR):" << endl;
    processInfo << "Step 4 (With MAR loaded load Data into MDR):" << endl;
    state.SetPCMARSelect(1);
    state.SetMDRload(1);
    state.SetBoe(1);
    state.SetS2op(0);
    state.SetALUop(3);
    state.SetAoe(0);
    state.SetS2op(0);
    state.SetMARload(0);
    addr = mar;
    s2 = b;
    data = b;
    mdr = data;
    PrintState();
    cout << "Step 5 (Write from MDR to MEM):" << endl;
    processInfo << "Step 5 (Write from MDR to MEM):" << endl;
    state.SetMemOp(0);
    state.SetMemWrite(1);
    state.SetMDRload(0);
    state.SetBoe(0);
    state.SetALUop(0);
    state.SetPCMARSelect(0);
    WriteMemory(mar, mdr, WORD);
    PrintState();
}

void DataPath::Sub(){
    cout << "Step 3 (Subtract B from A, Save to C): " << endl;
    processInfo << "Step 3 (Subtract B from A, Save to C): " << endl;
    state.SetAoe(1);
    state.SetBoe(1);
    state.SetALUop(1);
    state.SetCload(1);
    state.SetS2op(0);
    state.SetAload(0);
    state.SetBload(0);
    state.SetPCoeS1(0);
    state.SetPCload(0);
    s1 = a;
    s2 = b;
    dest = a - b;
    c = dest;
    PrintState();
    cout << "Step 4 (Save C to rd):" << endl;
    processInfo << "Step 4 (Save C to rd):" << endl;
    state.SetREGload(1);
    state.SetREGselect(0);
    state.SetAoe(0);
    state.SetBoe(0);
    state.SetCload(0);
    regFile[rd] = c;
    PrintState();
}