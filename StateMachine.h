//
// Created by Dylan Chariott on 2019-04-24.
//

#ifndef DLXSIMULATOR_STATEMACHINE_H
#define DLXSIMULATOR_STATEMACHINE_H

class StateMachine{
private:
    int S2op;
    int ALUop;
    int Cload;
    int REGload;
    int REGselect;
    int Aload;
    int Aoe;
    int Bload;
    int Boe;
    int IRload;
    int IRoeS1;
    int IRoeS2;
    int Reset;
    int PCload;
    int PCoeS1;
    int PCMARselect;
    int MARload;
    int MDRload;
    int MDRoeS2;
    int MemRead;
    int MemWrite;
    int MemOp;
public:
    StateMachine();
    const int GetS2op();
    void SetS2op(int S2op);
    const int GetALUop();
    void SetALUop(int ALUop);
    const int GetCload();
    void SetCload(int Cload);
    const int GetREGload();
    void SetREGload(int REGload);
    const int GetREGselect();
    void SetREGselect(int REGselect);
    const int GetAload();
    void SetAload(int Aload);
    const int GetAoe();
    void SetAoe(int Aoe);
    const int GetBload();
    void SetBload(int Bload);
    const int GetBoe();
    void SetBoe(int Boe);
    const int GetIRload();
    void SetIRload(int IRload);
    const int GetIRoeS1();
    void SetIRoeS1(int IRoeS1);
    const int GetIRoeS2();
    void SetIRoeS2(int IRoeS2);
    const int GetReset();
    void SetReset(int Reset);
    const int GetPCload();
    void SetPCload(int PCload);
    const int GetPCoeS1();
    void SetPCoeS1(int PCoeS1);
    const int GetPCMARselect();
    void SetPCMARSelect(int PCMARselect);
    const int GetMARload();
    void SetMARload(int MARload);
    const int GetMDRload();
    void SetMDRload(int MDRload);
    const int GetMDRoeS2();
    void SetMDRoeS2(int MDRoeS2);
    const int GetMemRead();
    void SetMemRead(int MemRead);
    const int GetMemWrite();
    void SetMemWrite(int MemWrite);
    const int GetMemOp();
    void SetMemOp(int MemOp);
};
#endif //DLXSIMULATOR_STATEMACHINE_H
