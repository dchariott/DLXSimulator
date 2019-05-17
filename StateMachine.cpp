//
// Created by Dylan Chariott on 2019-04-24.
//

#include "StateMachine.h"

StateMachine::StateMachine(){
    this->PCMARselect = 0;
}

const int StateMachine::GetS2op(){
    return this->S2op;
}

void StateMachine::SetS2op(int S2op){
    this->S2op = S2op;
}

const int StateMachine::GetALUop(){
    return this->ALUop;
}

void StateMachine::SetALUop(int ALUop){
    this->ALUop = ALUop;
}

const int StateMachine::GetCload(){
    return this->Cload;
}

void StateMachine::SetCload(int Cload){
    this->Cload = Cload;
}

const int StateMachine::GetREGload(){
    return this->REGload;
}

void StateMachine::SetREGload(int REGload){
    this->REGload = REGload;
}

const int StateMachine::GetREGselect(){
    return this->REGselect;
}

void StateMachine::SetREGselect(int REGselect){
    this-> REGselect = REGselect;
}

const int StateMachine::GetAload(){
    return this->Aload;
}

void StateMachine::SetAload(int Aload){
    this->Aload = Aload;
}

const int StateMachine::GetAoe(){
    return this->Aoe;
}

void StateMachine::SetAoe(int Aoe){
    this->Aoe = Aoe;
}

const int StateMachine::GetBload(){
    return this->Bload;
}

void StateMachine::SetBload(int Bload){
    this->Bload = Bload;
}

const int StateMachine::GetBoe(){
    return this->Boe;
}

void StateMachine::SetBoe(int Boe){
    this->Boe = Boe;
}

const int StateMachine::GetIRload(){
    return this->IRload;
}

void StateMachine::SetIRload(int IRload){
    this->IRload = IRload;
}

const int StateMachine::GetIRoeS1(){
    return this->IRoeS1;
}

void StateMachine::SetIRoeS1(int IRoeS1){
    this->IRoeS1 = IRoeS1;
}

const int StateMachine::GetIRoeS2(){
    return this->IRoeS2;
}

void StateMachine::SetIRoeS2(int IRoeS2){
    this->IRoeS2 = IRoeS2;
}

const int StateMachine::GetReset(){
    return this->Reset;
}

void StateMachine::SetReset(int Reset){
    this->Reset = Reset;
}

const int StateMachine::GetPCload(){
    return this->PCload;
}

void StateMachine::SetPCload(int PCload){
    this->PCload = PCload;
}

const int StateMachine::GetPCoeS1(){
    return this->PCoeS1;
}

void StateMachine::SetPCoeS1(int PCoeS1){
    this->PCoeS1 = PCoeS1;
}

const int StateMachine::GetPCMARselect(){
    return this->PCMARselect;
}

void StateMachine::SetPCMARSelect(int PCMARselect){
    this->PCMARselect = PCMARselect;
}

const int StateMachine::GetMARload(){
    return this->MARload;
}

void StateMachine::SetMARload(int MARload){
    this->MARload = MARload;
}

const int StateMachine::GetMDRload(){
    return this->MDRload;
}

void StateMachine::SetMDRload(int MDRload){
    this->MDRload = MDRload;
}

const int StateMachine::GetMDRoeS2(){
    return this->MDRoeS2;
}

void StateMachine::SetMDRoeS2(int MDRoeS2){
    this->MDRoeS2 = MDRoeS2;
}

const int StateMachine::GetMemRead(){
    return this->MemRead;
}

void StateMachine::SetMemRead(int MemRead){
    this->MemRead = MemRead;
}

const int StateMachine::GetMemWrite(){
    return this->MemWrite;
}

void StateMachine::SetMemWrite(int MemWrite){
    this->MemWrite = MemWrite;
}

const int StateMachine::GetMemOp(){
    return this->MemOp;
}

void StateMachine::SetMemOp(int MemOp){
    this->MemOp = MemOp;
}
