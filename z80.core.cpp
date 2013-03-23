// z80.core.cpp : Defines the entry point for the console application.
//
// z80.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "z80.core.h"

z80::z80(){
	_clock.m=0;
	_clock.t=0;
	_r.a=0;
	_r.b=0;
	_r.c=0;
	_r.d=0;
	_r.e=0;
	_r.f=0;
	_r.h=0;
	_r.l=0;
	_r.m=0;
	_r.t=0; 
	_r.sp=0;
	_r.pc=0;  //initialize all the registers to 0;

	/* initialize the Opcode for the Gameboy z80 */

	/*------------------0x----------------------*/

	_map[0]=&z80::print_status; //00
	_map[1]=&z80::LDBCnn; //01
	_map[2]=&z80::LDBCmA; //02
	_map[3]=&z80::INCBC; //03
	_map[4]=&z80::INCr_a; //04
	_map[5]=&z80::DECr_b; //05
	_map[6]=&z80::LDrn_b; //06
	_map[7]=&z80::RLCA;  //07
	_map[8]=&z80::LDSPnn; //08
	_map[9]=&z80::ADDHLBC; //09
	_map[10]=&z80::LDABCm; //0A
	_map[11]=&z80::DECBC; //0B
	_map[12]=&z80::INCr_c; //0C
	_map[13]=&z80::DECr_c; //0D
	_map[14]=&z80::LDrn_c; //0E
	_map[15]=&z80::RRCA; //0F

	/*------------------1x-----------------------*/

	_map[16]=&z80::DJNZn; //10
	_map[17]=&z80::LDDEnn; //11
	_map[18]=&z80::LDDEmA; //12
	_map[19]=&z80::INCDE; //13
	_map[20]=&z80::INCr_d; //14
	_map[21]=&z80::DECr_d; //15
	_map[22]=&z80::LDrn_d; //16
	_map[23]=&z80::RLA; //17
	_map[24]=&z80::JRn; //18
	_map[25]=&z80::ADDHLDE; //19
	_map[26]=&z80::LDADEm; //1A
	_map[27]=&z80::DECDE; //1B
	_map[28]=&z80::INCr_e; //1C
	_map[29]=&z80::DECr_e;  //1D
	_map[30]=&z80::LDrn_e; //1E
    _map[31]=&z80::RRA; //1F

	/*---------------------2x----------------------*/

	_map[32]=&z80::JPNZnn; //20
	_map[33]=&z80::LDHLnn; //21
	_map[34]=&z80::LDHLIA; //22
	_map[35]=&z80::INCHL; //23
	_map[36]=&z80::INCr_h; //24
	_map[37]=&z80::DECr_h; //25
	_map[38]=&z80::LDrn_h; //26
	_map[39]=&z80::XX; //27
	_map[40]=&z80::JRZn; //28
	_map[41]=&z80::ADDHLHL; //29
	_map[42]=&z80::LDAHLI; //2A
	_map[43]=&z80::DECHL; //2B
	_map[44]=&z80::INCr_l; //2C
	_map[45]=&z80::DECr_l; //2D
	_map[46]=&z80::LDrn_l; //2E
	_map[47]=&z80::CPL; //2F

	/*-----------------3x----------------------*/
	_map[48]=&z80::JRNCn; //30
	_map[49]=&z80::LDSPnn; //31
	_map[50]=&z80::LDHLDA; //32
	_map[51]=&z80::INCSP; //33
	_map[52]=&z80::INCHLm; //34
	_map[53]=&z80::DECHLm; //35
	_map[54]=&z80::LDHLmn; //36
	_map[55]=&z80::SCF; //37
	_map[56]=&z80::JRNCn; //38
	_map[57]=&z80::ADDHLSP; //39
	_map[58]=&z80::LDAHLD; //3A
	_map[59]=&z80::DECSP; //3B
	_map[60]=&z80::INCr_a; //3C
	_map[61]=&z80::DECr_a; //3D
	_map[62]=&z80::LDrn_a; //3E
	_map[63]=&z80::CCF;   //3F

	/*---------------4x------------------*/

	_map[64]=&z80::LDrr_bb; //40
	_map[65]=&z80::LDrr_bc; //41
	_map[66]=&z80::LDrr_bd; //42
	_map[67]=&z80::LDrr_be; //43
	_map[68]=&z80::LDrr_bh; //44
	_map[69]=&z80::LDrr_bl; //45
	_map[70]=&z80::LDrHLm_b; //46
	_map[71]=&z80::LDrr_ba; //47
	_map[72]=&z80::LDrr_cb; //48
	_map[73]=&z80::LDrr_cc; //49
	_map[74]=&z80::LDrr_cd; // 4A
	_map[75]=&z80::LDrr_ce; //4B
	_map[76]=&z80::LDrr_ch; //4C
	_map[77]=&z80::LDrr_cl; //4D
	_map[78]=&z80::LDrHLm_c; //4E
	_map[79]=&z80::LDrr_ca; //4F

	/*---------------------5x-----------------------*/
	_map[80]=&z80::LDrr_db; //50
	_map[81]=&z80::LDrr_dc; //51
	_map[82]=&z80::LDrr_dd; //52
	_map[83]=&z80::LDrr_de; //53
	_map[84]=&z80::LDrr_dh; //54
	_map[85]=&z80::LDrr_dl; //55
	_map[86]=&z80::LDrHLm_d; //56
	_map[87]=&z80::LDrr_da; //57
	_map[88]=&z80::LDrr_eb; //58
	_map[89]=&z80::LDrr_ec; //59
	_map[90]=&z80::LDrr_ed; //5A
	_map[91]=&z80::LDrr_ee; //5B
	_map[92]=&z80::LDrr_eh; //5C
	_map[93]=&z80::LDrr_el; //5D
	_map[94]=&z80::LDrHLm_e; //5E
	_map[95]=&z80::LDrr_ea; //5F

	/*----------------------6x----------------------*/

	_map[96]=&z80::LDrr_hb; //60
	_map[97]=&z80::LDrr_hc; //61
	_map[98]=&z80::LDrr_hd; //62
	_map[99]=&z80::LDrr_he; //63
	_map[100]=&z80::LDrr_hh; //64
	_map[101]=&z80::LDrr_hl; //65
	_map[102]=&z80::LDrHLm_h; //66
	_map[103]=&z80::LDrr_ha; //67
	_map[104]=&z80::LDrr_lb; //68
	_map[105]=&z80::LDrr_lc;  //69
	_map[106]=&z80::LDrr_ld;  //6A
	_map[107]=&z80::LDrr_le; // 6B
	_map[108]=&z80::LDrr_lh; //6C
	_map[109]=&z80::LDrr_ll; //6D
	_map[110]=&z80::LDrHLm_l; //6E
	_map[111]=&z80::LDrr_la; //6F

	/*-----------------------7x---------------------*/
	_map[112]=&z80::LDHLmr_b; //70
	_map[113]=&z80::LDHLmr_c; //71
	_map[114]=&z80::LDHLmr_d; //72
	_map[115]=&z80::LDHLmr_e; //73
	_map[116]=&z80::LDHLmr_h; //74
	_map[117]=&z80::LDHLmr_l; //75
	_map[118]=&z80::HALT; //76
	_map[119]=&z80::LDHLmr_a; //77
	_map[120]=&z80::LDrr_ab; //78
	_map[121]=&z80::LDrr_ac; //79
	_map[122]=&z80::LDrr_ad; //7A
	_map[123]=&z80::LDrr_ae; //7B
	_map[124]=&z80::LDrr_ah;//7C
	_map[125]=&z80::LDrr_al; //7D
	_map[126]=&z80::LDrHLm_a; //7E
	_map[127]=&z80::LDrr_aa; //7F

	/*---------------8x-----------------*/

	_map[128]=&z80::ADDr_b; //80
	_map[129]=&z80::ADDr_c; //81
	_map[130]=&z80::ADDr_d; //82
	_map[131]=&z80::ADDr_e; //83
	_map[132]=&z80::ADDr_h; //84
	_map[133]=&z80::ADDr_l; //85
	_map[134]=&z80::ADDHL; //86
	_map[135]=&z80::ADDr_a; //87
	_map[136]=&z80::ADCr_b; //88
	_map[137]=&z80::ADCr_c; //89
	_map[138]=&z80::ADCr_d; // 8A
	_map[139]=&z80::ADCr_e; //8B
	_map[140]=&z80::ADCr_h; //8C
	_map[141]=&z80::ADCr_l; //8D
	_map[142]=&z80::ADCHL; //8E
	_map[143]=&z80::ADCr_a; //8F

	/*----------------9x-----------------*/
	_map[144]=&z80::SUBr_b; //90
	_map[145]=&z80::SUBr_c; //91
	_map[146]=&z80::SUBr_d; //92
	_map[147]=&z80::SUBr_e; //93
	_map[148]=&z80::SUBr_h; //94
	_map[149]=&z80::SUBr_l; //95
	_map[150]=&z80::SUBHL; //96
	_map[151]=&z80::SUBr_a; //97
	_map[152]=&z80::SBCr_b; //98
	_map[153]=&z80::SBCr_c; //99
	_map[154]=&z80::SBCr_d; //9A
	_map[155]=&z80::SBCr_e; //9B
	_map[156]=&z80::SBCr_h; //9C
	_map[157]=&z80::SBCr_l; //9D
	_map[158]=&z80::SBCHL; //9E
	_map[159]=&z80::SBCr_a; //9F

	/*--------------------Ax----------------------*/
	_map[160]=&z80::ANDr_b; //A0
	_map[161]=&z80::ANDr_c; //A1
	_map[162]=&z80::ANDr_d; //A2
	_map[163]=&z80::ANDr_e; //A3
	_map[164]=&z80::ANDr_h;  //A4
	_map[165]=&z80::ANDr_l ; //A5
	_map[166]=&z80::ANDHL; //A6
	_map[167]=&z80::ANDr_a; //A7
	_map[168]=&z80::XORr_b;  //A8
	_map[169]=&z80::XORr_c; //A9
	_map[170]=&z80::XORr_d;  //AA
	_map[171]=&z80::XORr_e;  //AB
	_map[172]=&z80::XORr_h; //AC
	_map[173]=&z80::XORr_l; //AD
	_map[174]=&z80::XORHL; //AE
	_map[175]=&z80::XORr_a; //AF

	/*---------------------Bx-----------------------*/

	_map[176]=&z80::ORr_b; //B0
	_map[177]=&z80::ORr_c; //B1
	_map[178]=&z80::ORr_d; //B2
	_map[179]=&z80::ORr_e; //B3
	_map[180]=&z80::ORr_h; //B4
	_map[181]=&z80::ORr_l; //B5
	_map[182]=&z80::ORHL; //B6
	_map[183]=&z80::ORr_a; //B7
	_map[184]=&z80::CPr_b;  //B8
	_map[185]=&z80::CPr_c; //B9
	_map[186]=&z80::CPr_d; //BA
	_map[187]=&z80::CPr_e; //BB
	_map[188]=&z80::CPr_h; //BC
	_map[189]=&z80::CPr_l; //BD
	_map[190]=&z80::CPHL; //BE
	_map[191]=&z80::CPr_a; //BF

	/*--------------------Cx----------------------*/
	_map[192]=&z80::RETNZ; //C0
	_map[193]=&z80::POPBC; //C1
	_map[194]=&z80::JPNZnn; //C2
	_map[195]=&z80::JPnn; //C3
	_map[196]=&z80::CALLNZnn; //C4
	_map[197]=&z80::PUSHBC; //C5
	_map[198]=&z80::ADDn; //C6
	_map[199]=&z80::RST00; //C7
	_map[200]=&z80::RETZ; //C8
	_map[201]=&z80::RET; //C9
	_map[202]=&z80::JPZnn; //CA
	_map[203]=&z80::MAPcb; //CB
	_map[204]=&z80::CALLZnn; //CC
	_map[205]=&z80::CALLnn; //CD
	_map[206]=&z80::ADCn; //CE
	_map[207]=&z80::RST08; //CF

	/*---------------------Dx-----------------------*/

	_map[208]=&z80::RETNC; //D0
	_map[209]=&z80::POPDE; //D1
	_map[210]=&z80::JPNCnn; //D2
	_map[211]=&z80::XX; //D3
	_map[212]=&z80::CAllNCnn; //D4
	_map[213]=&z80::PUSHDE; //D5
	_map[214]=&z80::SUBn; //D6
	_map[215]=&z80::RST10; //D7
	_map[216]=&z80::RETC; //D8;
	_map[217]=&z80::RETI; //D9
	_map[218]=&z80::JPCnn; //DA
	_map[219]=&z80::XX; //DB
	_map[220]=&z80::CALLCnn; //DC
	_map[221]=&z80::XX; //DD;
	_map[222]=&z80::SBCn; //DE
	_map[223]=&z80::RST18; //DF

	/*----------------------Ex---------------------*/

	_map[224]=&z80::LDIOnA; //E0
	_map[225]=&z80::POPDE; //E1
	_map[226]=&z80::LDIOCA; //E2
	_map[227]=&z80::XX; //E3
	_map[228]=&z80::XX; //E4
	_map[229]=&z80::PUSHHL; //E5
	_map[230]=&z80::ANDn; //E6
	_map[231]=&z80::RST20; //E7
	_map[232]=&z80::ADDSPn; //E8
	_map[233]=&z80::JPHL; //E9
	_map[234]=&z80::LDmmA; //EA
	_map[235]=&z80::XX; //EB
	_map[236]=&z80::XX; //EC
	_map[237]=&z80::XX; //ED
	_map[238]=&z80::XORn; //EE
	_map[239]=&z80::RST28; //EF

	/*------------------------Fx-------------------------*/

	_map[240]=&z80::LDAIOn; //F0
	_map[241]=&z80::POPAF; //F1
	_map[242]=&z80::XX; //F2
	_map[243]=&z80::DI; //F3
	_map[244]=&z80::XX; //F4
	_map[245]=&z80::PUSHAF; //F5
	_map[246]=&z80::ORn; //F6 
	_map[247]=&z80::RST30; //F7
	_map[248]=&z80::LDHLSPn; //F8
	_map[249]=&z80::XX; //F9
	_map[250]=&z80::LDAmm; //FA
	_map[251]=&z80::EI; //FB
	_map[252]=&z80::XX; //FC
	_map[253]=&z80::XX; //FD
	_map[254]=&z80::CPn; //FE
	_map[255]=&z80::RST38; //FF

















	
















};

/* Load/store function s imulation*/

void z80::LDrr_aa(){
	_r.a=_r.a;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ab(){
	_r.a=_r.a;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ac(){
	_r.a=_r.c;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ad(){
	_r.a=_r.d;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ae(){
	_r.a=_r.e;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ah(){
	_r.a=_r.h;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_al(){
	_r.a=_r.l;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ba(){
	_r.b=_r.a;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_bb(){
	_r.b=_r.b;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_bc(){
	_r.b=_r.c;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_bd(){
	_r.b=_r.d;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_be(){
	_r.b=_r.e;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_bh(){
	_r.b=_r.h;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_bl(){
	_r.b=_r.l;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ca(){
	_r.c=_r.a;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_cb(){
	_r.c=_r.b;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_cc(){
	_r.c=_r.c;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_cd(){
	_r.c=_r.d;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ce(){
	_r.c=_r.e;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ch(){
	_r.c=_r.h;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_cl(){
	_r.c=_r.l;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_da(){
	_r.d=_r.a;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_db(){
	_r.d=_r.b;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_dc(){
	_r.d=_r.c;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_dd(){
	_r.d=_r.d;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_de(){
	_r.d=_r.e;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_dh(){
	_r.d=_r.h;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_dl(){
	_r.d=_r.l;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ea(){
	_r.e=_r.a;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_eb(){
	_r.e=_r.b;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ec(){
	_r.e=_r.c;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ed(){
	_r.e=_r.d;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ee(){
	_r.e=_r.e;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_eh(){
	_r.e=_r.h;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_el(){
	_r.e=_r.l;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ha(){
	_r.h=_r.a;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_hb(){
	_r.h=_r.b;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_hc(){
	_r.h=_r.c;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_hd(){
	_r.h=_r.d;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_he(){
	_r.h=_r.e;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_hh(){
	_r.h=_r.h;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_hl(){
	_r.h=_r.l;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_la(){
	_r.l=_r.a;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_lb(){
	_r.l=_r.b;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_lc(){
	_r.l=_r.c;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ld(){
	_r.l=_r.d;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_le(){
	_r.l=_r.e;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_lh(){
	_r.l=_r.h;
	_r.m=1;
	_r.t=4;
};

void z80::LDrr_ll(){
	_r.l=_r.l;
	_r.m=1;
	_r.t=4;
};

/*--------*/
void z80::LDrHLm_a(){
	_r.a=_mmu.rb((_r.h<<8)+_r.l);
	_r.m=2;
	_r.t=8;
};

void z80::LDrHLm_b(){
	_r.b=_mmu.rb((_r.h<<8)+_r.l);
	_r.m=2;
	_r.t=8;
};

void z80::LDrHLm_c(){
	_r.c=_mmu.rb((_r.h<<8)+_r.l);
	_r.m=2;
	_r.t=8;
};

void z80::LDrHLm_d(){
	_r.d=_mmu.rb((_r.h<<8)+_r.l);
	_r.m=2;
	_r.t=8;
};

void z80::LDrHLm_e(){
	_r.e=_mmu.rb((_r.h<<8)+_r.l);
	_r.m=2;
	_r.t=8;
};

void z80::LDrHLm_h(){
	_r.h=_mmu.rb((_r.h<<8)+_r.l);
	_r.m=2;
	_r.t=8;
};

void z80::LDrHLm_l(){
	_r.l=_mmu.rb((_r.h<<8)+_r.l);
	_r.m=2;
	_r.t=8;
};

/*----------------*/

void z80::LDHLmr_a(){
	_mmu.wb((_r.h<<8)+_r.l,_r.a);
	_r.m=2;
	_r.t=4;
};

void z80::LDHLmr_b(){
	_mmu.wb((_r.h<<8)+_r.l,_r.b);
	_r.m=2;
	_r.t=4;
};

void z80::LDHLmr_c(){
	_mmu.wb((_r.h<<8)+_r.l,_r.c);
	_r.m=2;
	_r.t=4;
};

void z80::LDHLmr_d(){
	_mmu.wb((_r.h<<8)+_r.l,_r.d);
	_r.m=2;
	_r.t=4;
};

void z80::LDHLmr_e(){
	_mmu.wb((_r.h<<8)+_r.l,_r.e);
	_r.m=2;
	_r.t=4;
};

void z80::LDHLmr_h(){
	_mmu.wb((_r.h<<8)+_r.l,_r.h);
	_r.m=2;
	_r.t=4;
};
  
void z80::LDHLmr_l(){
	_mmu.wb((_r.h<<8)+_r.l,_r.l);
	_r.m=2;
	_r.t=4;
};


/*----------------*/

void z80::LDrn_a(){
	_r.a=_mmu.rb(_r.pc);
	_r.pc++;
	_r.m=2;
	_r.t=8;
};

void z80::LDrn_b(){
	_r.b=_mmu.rb(_r.pc);
	_r.pc++;
	_r.m=2;
	_r.t=8;
};

void z80::LDrn_c(){
	_r.c=_mmu.rb(_r.pc);
	_r.pc++;
	_r.m=2;
	_r.t=8;
};

void z80::LDrn_d(){
	_r.d=_mmu.rb(_r.pc);
	_r.pc++;
	_r.m=2;
	_r.t=8;
};

void z80::LDrn_e(){
	_r.e=_mmu.rb(_r.pc);
	_r.pc++;
	_r.m=2;
	_r.t=8;
};

void z80::LDrn_h(){
	_r.h=_mmu.rb(_r.pc);
	_r.pc++;
	_r.m=2;
	_r.t=8;
};

void z80::LDrn_l(){
	_r.l=_mmu.rb(_r.pc);
	_r.pc++;
	_r.m=2;
	_r.t=8;
};


/*-------------------*/

void z80::LDHLmn(){

	_mmu.wb((_r.h<<8)+_r.l,_mmu.rb(_r.pc));
	_r.pc++;
	_r.m=2;
	_r.t=8;
};

void z80::LDBCmA(){
	_mmu.wb((_r.b<<8)+_r.c,_r.a);
	_r.m=2;
	_r.t=8;
};


void z80::LDDEmA(){
	_mmu.wb((_r.d<<8)+_r.e,_r.a);
	_r.m=2;
	_r.t=8;
};

void z80::LDmmA(){
	_mmu.wb(_mmu.rw(_r.pc),_r.a);
	_r.pc++;
	_r.m=2;
	_r.t=8;
};

void  z80::LDABCm(){
	_r.a=_mmu.rb((_r.b<<8)+_r.c);
	_r.m=2;
	_r.t=8;
};

void z80::LDADEm(){
	_r.a=_mmu.rb((_r.d<<8)+_r.e);
	_r.m=2;
	_r.t=8;
};

void z80::LDAmm(){
	_r.a=_mmu.rb(_mmu.rb(_r.pc));
	_r.m=2;
	_r.t=8;
};

void z80::LDBCnn(){
	_r.c=_mmu.rb(_r.pc);
	_r.b=_mmu.rb(_r.pc+1);
	_r.pc+=2;
	_r.m=3;
	_r.t=12;
};

void z80::LDDEnn(){
	_r.e=_mmu.rb(_r.pc);
	_r.d=_mmu.rb(_r.pc+1);
	_r.pc+=2;
	_r.m=3;
	_r.t=12;
};

void z80::LDHLnn(){
	_r.l=_mmu.rb(_r.pc);
	_r.h=_mmu.rb(_r.pc+1);
	_r.pc+=2;
	_r.m=3;
	_r.t=12;
};

void z80::LDSPnn(){
	_r.sp=_mmu.rw(_r.pc);
	_r.pc+=2;
	_r.m=3;
	_r.t=12;
};

void z80::LDHLmm(){
	byte i=_mmu.rw(_r.pc);
	_r.pc+=2;
	_r.l=_mmu.rb(i);
	_r.h=_mmu.rb(i+1);
	_r.m=5;
	_r.t=20;
};

void z80::LDmmHL(){
	byte i=_mmu.rw(_r.pc);
	_r.pc+=2;
	_mmu.ww(i,(_r.h<<8)+_r.l);
	_r.m=5;
	_r.t=20;
};

void z80::LDHLIA(){
	_mmu.wb((_r.h<<8)+_r.l,_r.a);
	_r.l=(_r.l+1)&255;
	if(!_r.l)_r.h=(_r.h+1)&255;
	_r.m=2;
	_r.t=8;
};


void z80::LDAHLI(){
	_r.a=_mmu.rb((_r.h<<8)+_r.l);
	_r.l=(_r.l+1)&255;
	if(!_r.l)_r.h=(_r.h+1)&255;
	_r.m=2;
	_r.t=8;
};


void z80::LDHLDA(){
	_mmu.wb((_r.h<<8)+_r.l,_r.a);
	_r.l=(_r.l-1)&255;
	if(!_r.l)_r.h=(_r.h-1)&255;
	_r.m=2;
	_r.t=8;
};

void z80::LDAHLD(){
	_r.a=_mmu.rb((_r.h<<8)+_r.l);
	_r.l=(_r.l-1)&255;
	if(!_r.l)_r.h=(_r.h-1)&255;
	_r.m=2;
	_r.t=8;
};


void z80::LDAIOn(){
	_r.a=_mmu.rb(0xFF00+_mmu.rb(_r.pc));
	_r.pc++;
	_r.m=3;
	_r.t=12;
};
   
void z80::LDIOnA(){
	_mmu.wb(0xFF00+_mmu.rb(_r.pc),_r.a);
	_r.pc++;
	_r.m=3;
	_r.t=12;
};

void z80::LDAIOC(){
	_r.a=_mmu.rb(0xFF00+_r.c);
	_r.m=2;
	_r.t=8;
};

void z80::LDIOCA(){
	_mmu.wb(0xFF00+_r.c,_r.a);
	_r.m=2;
	_r.t=8;
};

void z80::LDHLSPn(){
	byte i=_mmu.rb(_r.pc);
	if(i>127)i=-((~i+1)&255);
	_r.pc++;
	i+=_r.sp;
	_r.h=(i>>8)&255;
	_r.l=i&255;
	_r.m=3;
	_r.t=12;
};

/*-----------------------------*/

void z80::SWAPr_a(){
	byte tr=_r.a;
	_r.a=_mmu.rb((_r.h<<8)+_r.l);
	_mmu.wb((_r.h<<8)+_r.l,tr);
	_r.m=4;
	_r.t=16;
};

void z80::SWAPr_b(){
	byte tr=_r.b;
	_r.b=_mmu.rb((_r.h<<8)+_r.l);
	_mmu.wb((_r.h<<8)+_r.l,tr);
	_r.m=4;
	_r.t=16;
};
void z80::SWAPr_c(){
	byte tr=_r.c;
	_r.c=_mmu.rb((_r.h<<8)+_r.l);
	_mmu.wb((_r.h<<8)+_r.l,tr);
	_r.m=4;
	_r.t=16;
};

void z80::SWAPr_d(){
	byte tr=_r.d;
	_r.d=_mmu.rb((_r.h<<8)+_r.l);
	_mmu.wb((_r.h<<8)+_r.l,tr);
	_r.m=4;
	_r.t=16;
};

void z80::SWAPr_e(){
	byte tr=_r.e;
	_r.e=_mmu.rb((_r.h<<8)+_r.l);
	_mmu.wb((_r.h<<8)+_r.l,tr);
	_r.m=4;
	_r.t=16;
};

void z80::SWAPr_h(){
	byte tr=_r.h;
	_r.h=_mmu.rb((_r.h<<8)+_r.l);
	_mmu.wb((_r.h<<8)+_r.l,tr);
	_r.m=4;
	_r.t=16;
};

void z80::SWAPr_l(){
	byte tr=_r.l;
	_r.l=_mmu.rb((_r.h<<8)+_r.l);
	_mmu.wb((_r.h<<8)+_r.l,tr);
	_r.m=4;
	_r.t=16;
};

/* Data Processing*/

void z80::ADDr_a(){
	_r.a+=_r.a; //Add e to a.
    fz(_r.a);// clear flag to 0. // check for zero
	if(_r.a>255)_r.f|=0x10; //check for if the value is overflow.
	_r.a&=255; // mask for 8 bits.
	_r.m=1; 
	_r.t=4; //1 M-time taken

};

void z80::ADDr_b(){
	_r.a+=_r.b; //Add b to a.
	fz(_r.a); // clear flag to 0. // check for zero
	if(_r.a>255)_r.f|=0x10; //check for if the value is overflow.
	_r.a&=255; // mask for 8 bits.
	_r.m=1; 
	_r.t=4; //1 M-time taken

};

void z80::ADDr_c(){
	_r.a+=_r.c; //Add c to a.
	fz(_r.a); // clear flag to 0. // check for zero
	if(_r.a>255)_r.f|=0x10; //check for if the value is overflow.
	_r.a&=255; // mask for 8 bits.
	_r.m=1; 
	_r.t=4; //1 M-time taken

};

void z80::ADDr_d(){
	_r.a+=_r.d; //Add d to a.
	fz(_r.a); // clear flag to 0. // check for zero
	if(_r.a>255)_r.f|=0x10; //check for if the value is overflow.
	_r.a&=255; // mask for 8 bits.
	_r.m=1; 
	_r.t=4; //1 M-time taken

};

void z80::ADDr_e(){
	_r.a+=_r.e; //Add e to a.
	fz(_r.a); // clear flag to 0. // check for zero
	if(_r.a>255)_r.f|=0x10; //check for if the value is overflow.
	_r.a&=255; // mask for 8 bits.
	_r.m=1; 
	_r.t=4; //1 M-time taken

};

void z80::ADDr_h(){
	_r.a+=_r.h; //Add h to a.
	fz(_r.a); // clear flag to 0. // check for zero
	if(_r.a>255)_r.f|=0x10; //check for if the value is overflow.
	_r.a&=255; // mask for 8 bits.
	_r.m=1; 
	_r.t=4; //1 M-time taken

};

void z80::ADDr_l(){
	_r.a+=_r.l; //Add l to a.
	fz(_r.a); // clear flag to 0. // check for zero
	if(_r.a>255)_r.f|=0x10; //check for if the value is overflow.
	_r.a&=255; // mask for 8 bits.
	_r.m=1; 
	_r.t=4; //1 M-time taken

};

/*---------------------*/

void z80::ADDHL(){
	_r.a+=_mmu.rb((_r.h<<8)+_r.l);
	fz(_r.a);
	if(_r.a>255)_r.f|=0x10;
	_r.a&=255;
	_r.m=2;
	_r.t=8;
};

void z80::ADDn(){
	_r.a+=_mmu.rb(_r.pc);
	_r.pc++;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x10;
	_r.a&=255;
	_r.m=2;
	_r.t=8;
};

void z80::ADDHLBC(){

	byte hl=(_r.h<<8)+_r.l;
	hl+=(_r.b<<8)+_r.c;
	if(hl>65535)_r.f|=0x10;
	else _r.f&=0xEF;
	_r.h=(hl>>8)&255;
	_r.l=hl&255;
	_r.m=3;
    _r.t=12;
};

void z80::ADDHLDE(){

	byte hl=(_r.h<<8)+_r.l;
	hl+=(_r.d<<8)+_r.e;
	if(hl>65535)_r.f|=0x10;
	else _r.f&=0xEF;
	_r.h=(hl>>8)&255;
	_r.l=hl&255;
	_r.m=3;
    _r.t=12;
};

void z80::ADDHLHL(){

	byte hl=(_r.h<<8)+_r.l;
	hl+=(_r.h<<8)+_r.l;
	if(hl>65535)_r.f|=0x10;
	else _r.f&=0xEF;
	_r.h=(hl>>8)&255;
	_r.l=hl&255;
	_r.m=3;
    _r.t=12;
};

void z80::ADDHLSP(){

	byte hl=(_r.h<<8)+_r.l;
	hl+=_r.pc;
	if(hl>65535)_r.f|=0x10;
	else _r.f&=0xEF;
	_r.h=(hl>>8)&255;
	_r.l=hl&255;
	_r.m=3;
    _r.t=12;
};

void z80::ADDSPn(){
     byte i=_mmu.rb(_r.pc);
	 if(i>127)i=-((~i+1)&255);
	 _r.pc++;
	 _r.sp+=i;
	 _r.sp+=i;
	 _r.m=4;
	 _r.t=16;
};

void z80::ADCr_b(){
	_r.a+=_r.b;
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::ADCr_c(){
	_r.a+=_r.c;
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::ADCr_d(){
	_r.a+=_r.d;
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};
void z80::ADCr_e(){
	_r.a+=_r.e;
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::ADCr_h(){
	_r.a+=_r.h;
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::ADCr_l(){
	_r.a+=_r.l;
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};
void z80::ADCr_a(){
	_r.a+=_r.a;
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::ADCHL(){
	_r.a+=_mmu.rb((_r.h<8)+_r.l);
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::ADCn(){
	_r.a+=_mmu.rb(_r.pc);
	_r.pc++;
	_r.a+=(_r.f&0x10)?1:0;
	fz(_r.a);
	if(_r.a>255)_r.f|=0x10;
	_r.a&=255;
	_r.m=2;
	_r.t=8;
};

/*---------------------*/
void z80::SUBr_a(){
	_r.a-=_r.a;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::SUBr_b(){
	_r.a-=_r.b;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::SUBr_c(){
	_r.a-=_r.c;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::SUBr_d(){
	_r.a-=_r.d;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::SUBr_e(){
	_r.a-=_r.e;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::SUBr_h(){
	_r.a-=_r.h;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::SUBr_l(){
	_r.a-=_r.l;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x01;
	_r.a&=255;
	_r.m=1;
	_r.t=4;
};

void z80::SUBHL(){
	_r.a-=_mmu.rb((_r.h<<8)+_r.l);
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=2;
	_r.t=8;
};

void z80::SUBn(){
    _r.a-=_mmu.rb(_r.pc);
	_r.pc++;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=2;
	_r.t=8;
};
/*----------------------*/

void z80::SBCr_a(){
	_r.a-=_r.a;
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
    _r.t=4;
};

void z80::SBCr_b(){
    _r.a-=_r.b;
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
    _r.t=4;
};

void z80::SBCr_c(){
	_r.a-=_r.c;
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
    _r.t=4;
};

void z80::SBCr_d(){
	_r.a-=_r.b;
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
    _r.t=4;
};

void z80::SBCr_e(){
	_r.a-=_r.e;
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
    _r.t=4;
};

void z80::SBCr_h(){
    _r.a-=_r.h
		;
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
    _r.t=4;
};

void  z80::SBCr_l(){
	_r.a-=_r.l;
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
    _r.t=4;
};

void z80::SBCHL(){
	_r.a-=_mmu.rb((_r.h<<8)+_r.l);
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=1;
    _r.t=4;
};

void z80::SBCn(){
	_r.a-=_mmu.rb(_r.pc);
	_r.pc++;
	_r.a-=(_r.f&0x10)?1:0;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=2;
    _r.t=8;
};

/*-----------------------------*/
void z80::CPr_a(){
	byte i=_r.a;
	i-=_r.a;
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=1;
	_r.t=4;
};

void z80::CPr_b(){
	byte i=_r.a;
	i-=_r.b;
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=1;
	_r.t=4;
};

void z80::CPr_c(){
	byte i=_r.a;
	i-=_r.c;
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=1;
	_r.t=4;
};

void z80::CPr_d(){
	byte i=_r.a;
	i-=_r.d;
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=1;
	_r.t=4;
};

void z80::CPr_e(){
	byte i=_r.a;
	i-=_r.e;
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=1;
	_r.t=4;
};

void z80::CPr_h(){
	byte i=_r.a;
	i-=_r.h;
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=1;
	_r.t=4;
};

void z80::CPr_l(){
	byte i=_r.a;
	i-=_r.l;
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=1;
	_r.t=4;
};

void z80::CPHL(){
	byte i=_r.a;
	i-=_mmu.rb((_r.h<<8)+_r.l);
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=2;
	_r.t=8;
};



void z80::CPn(){
	byte i=_r.a;
	i-=_mmu.rb(_r.pc);
	_r.pc++;
	fz(i,1);
	if(i<0)_r.f|=0x10;
	i&=255;
	_r.m=2;
	_r.t=8;
};

/*----------------------*/
void z80::ANDr_a(){
	_r.a&=_r.a;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ANDr_b(){
	_r.a&=_r.b;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ANDr_c(){
	_r.a&=_r.c;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ANDr_d(){
	_r.a&=_r.d;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ANDr_e(){
	_r.a&=_r.e;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ANDr_h(){
	_r.a&=_r.h;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ANDr_l(){
	_r.a&=_r.l;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ANDHL(){
	_r.a&=_mmu.rb((_r.h<<8)+_r.l);
	_r.a&=255;
	fz(_r.a);
	_r.m=2;
	_r.t=8;
};

void z80::ANDn(){
	_r.a&=_mmu.rb(_r.pc);
	_r.pc++;
	_r.a&=255;
	fz(_r.a);
	_r.m=2;
	_r.t=8;
};

/*---------------------*/

void z80::ORr_a(){
	_r.a|=_r.a;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ORr_b(){
	_r.a|=_r.b;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ORr_c(){
	_r.a|=_r.c;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ORr_d(){
	_r.a|=_r.d;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ORr_e(){
	_r.a|=_r.e;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ORr_h(){
	_r.a|=_r.h;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ORr_l(){
	_r.a|=_r.l;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::ORHL(){
	_r.a|=_mmu.rb((_r.h<<8)+_r.l);
	_r.a&=255;
	fz(_r.a);
	_r.m=2;
	_r.t=8;
};

void z80::ORn(){
	_r.a|=_mmu.rb(_r.pc);
	_r.pc++;
	_r.a&=255;
	fz(_r.a);
	_r.m=2;
	_r.t=8;
};

/*---------------------*/
void z80::XORr_a(){
	_r.a^=_r.a;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::XORr_b(){
	_r.a^=_r.b;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::XORr_c(){
	_r.a^=_r.c;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::XORr_d(){
	_r.a^=_r.d;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::XORr_e(){
	_r.a^=_r.e;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::XORr_h(){
	_r.a^=_r.h;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::XORr_l(){
	_r.a^=_r.l;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::XORHL(){
	_r.a^=_mmu.rb((_r.h<<8)+_r.l);
	_r.a&=255;
	fz(_r.a);
	_r.m=2;
	_r.t=8;
};

void z80::XORn(){
	_r.a^=_mmu.rb(_r.pc);
	_r.pc++;
	_r.a&=255;
	fz(_r.a);
	_r.m=2;
	_r.t=8;
};

/*-------------------*/

void z80::INCr_a(){
	_r.a++;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::INCr_b(){
	_r.b++;
	_r.b&=255;
	fz(_r.b);
	_r.m=1;
	_r.t=4;
};

void z80::INCr_c(){
	_r.c++;
	_r.c&=255;
	fz(_r.c);
	_r.m=1;
	_r.t=4;
};

void z80::INCr_d(){
	_r.d++;
	_r.d&=255;
	fz(_r.d);
	_r.m=1;
	_r.t=4;
};

void z80::INCr_e(){
	_r.e++;
	_r.e&=255;
	fz(_r.e);
	_r.m=1;
	_r.t=4;
};

void z80::INCr_h(){
	_r.h++;
	_r.h&=255;
	fz(_r.h);
	_r.m=1;
	_r.t=4;
};

void z80::INCr_l(){
	_r.l++;
	_r.l&=255;
	fz(_r.l);
	_r.m=1;
	_r.t=4;
};

void z80::INCHLm(){
	byte i=_mmu.rb((_r.h<<8)+_r.l)+1;
	i&=255;
	_mmu.wb((_r.h<<8)+_r.l,i);
	fz(i);
	_r.m=3;
	_r.t=12;
};

/*----------------------------*/
void z80::DECr_a(){
	_r.a--;
	_r.a&=255;
	fz(_r.a);
	_r.m=1;
	_r.t=4;
};

void z80::DECr_b(){
	_r.b--;
	_r.b&=255;
	fz(_r.b);
	_r.m=1;
	_r.t=4;
};

void z80::DECr_c(){
	_r.c--;
	_r.c&=255;
	fz(_r.c);
	_r.m=1;
	_r.t=4;
};

void z80::DECr_d(){
	_r.d--;
	_r.d&=255;
	fz(_r.d);
	_r.m=1;
	_r.t=4;
};

void z80::DECr_e(){
	_r.e--;
	_r.e&=255;
	fz(_r.e);
	_r.m=1;
	_r.t=4;
};

void z80::DECr_h(){
	_r.h--;
	_r.h&=255;
	fz(_r.h);
	_r.m=1;
	_r.t=4;
};

void z80::DECr_l(){
	_r.l--;
	_r.l&=255;
	fz(_r.l);
	_r.m=1;
	_r.t=4;
};

void z80::DECHLm(){
	byte i=_mmu.rb((_r.h<<8)+_r.l)-1;
    i&=255;
	_mmu.wb((_r.h<<8)+_r.l,i);
	fz(i);
	_r.m=3;
	_r.t=12;
};

/*------------------------------------*/
void z80::INCBC(){
	_r.c=(_r.c+1)&255;
	if(!_r.c)_r.b=(_r.b+1)&255;
	_r.m=1;
	_r.t=4;
};

void z80::INCDE(){
    _r.e=(_r.e+1)&255;
	if(!_r.e)_r.d=(_r.d+1)&255;
	_r.m=1;
	_r.t=4;
};

void z80::INCHL(){
    _r.l=(_r.l+1)&255;
	if(!_r.l)_r.h=(_r.h+1)&255;
	_r.m=1;
	_r.t=4;
};

void z80::INCSP(){
	_r.sp=(_r.pc+1)&65535;
	_r.m=1;
	_r.t=4;
};

/*-------------------------------*/

void z80::DECBC(){
	_r.c=(_r.c-1)&255;
	if(_r.c==255)_r.b=(_r.b-1)&255;
	_r.m=1;
	_r.t=4;
};

void z80::DECDE(){
	_r.e=(_r.e-1)&255;
	if(_r.e==255)_r.d=(_r.d-1)&255;
	_r.m=1;
	_r.t=4;
};

void z80::DECHL(){
	_r.l=(_r.l-1)&255;
	if(_r.l==255)_r.h=(_r.h-1)&255;
	_r.m=1;
	_r.t=4;
};

void z80::DECSP(){
	_r.sp=(_r.pc-1)&65535;
	_r.m=1;
	_r.t=4;
};


/*-------------------------------------------*/

void z80::BIT0a(){
	fz(_r.a&0x01);
	_r.m=2;
	_r.t=8;
};

void z80::BIT0b(){
	fz(_r.b&0x01);
	_r.m=2;
	_r.t=8;
};

void z80::BIT0c(){
	fz(_r.c&0x01);
	_r.m=2;
	_r.t=8;
};

void z80::BIT0d(){
	fz(_r.d&0x01);
	_r.m=2;
	_r.t=8;
};

void z80::BIT0e(){
	fz(_r.e&0x01);
	_r.m=2;
	_r.t=8;
};

void z80::BIT0h(){
	fz(_r.h&0x01);
	_r.m=2;
	_r.t=8;
};

void z80::BIT0l(){
	fz(_r.l&0x01);
	_r.m=2;
	_r.t=8;
};

void z80::BIT0m(){
	fz(_mmu.rb((_r.h<<8)+_r.l&0x01));
	_r.m=3;
	_r.t=12;
};

void z80::BIT1a(){
	fz(_r.a&0x02);
	_r.m=2;
	_r.t=8;
};

void z80::BIT1b(){
	fz(_r.b&0x02);
	_r.m=2;
	_r.t=8;
};

void z80::BIT1c(){
	fz(_r.c&0x02);
	_r.m=2;
	_r.t=8;
};

void z80::BIT1d(){
	fz(_r.d&0x02);
	_r.m=2;
	_r.t=8;
};

void z80::BIT1e(){
	fz(_r.e&0x02);
	_r.m=2;
	_r.t=8;
};

void z80::BIT1h(){
	fz(_r.h&0x02);
	_r.m=2;
	_r.t=8;
};

void z80::BIT1l(){
	fz(_r.l&0x02);
	_r.m=2;
	_r.t=8;
};

void z80::BIT1m(){
	fz(_mmu.rb((_r.h<<8)+_r.l)&0x02);
	_r.m=3;
	_r.t=12;
};

void z80::BIT2a(){
	fz(_r.a&0x04);
	_r.m=2;
	_r.t=8;
};

void z80::BIT2b(){
	fz(_r.b&0x04);
	_r.m=2;
	_r.t=8;
};

void z80::BIT2c(){
	fz(_r.c&0x04);
	_r.m=2;
	_r.t=8;
};

void z80::BIT2d(){
	fz(_r.d&0x04);
	_r.m=2;
	_r.t=8;
};

void z80::BIT2e(){
	fz(_r.e&0x04);
	_r.m=2;
	_r.t=8;
};

void z80::BIT2h(){
	fz(_r.h&0x04);
	_r.m=2;
	_r.t=8;
};

void z80::BIT2l(){
	fz(_r.l&0x04);
	_r.m=2;
	_r.t=8;
};

void z80::BIT2m(){
	fz(_mmu.rb((_r.h<<8)+_r.l)&0x04);
	_r.m=3;
	_r.t=12;
};

void z80::BIT3a(){
	fz(_r.a&0x08);
	_r.m=2;
	_r.t=8;
};

void z80::BIT3b(){
	fz(_r.b&0x08);
	_r.m=2;
	_r.t=8;
};

void z80::BIT3c(){
	fz(_r.c&0x08);
	_r.m=2;
	_r.t=8;
};

void z80::BIT3d(){
	fz(_r.d&0x08);
	_r.m=2;
	_r.t=8;
};

void z80::BIT3e(){
	fz(_r.e&0x08);
	_r.m=2;
	_r.t=8;
};

void z80::BIT3h(){
	fz(_r.h&0x08);
	_r.m=2;
	_r.t=8;
};

void z80::BIT3l(){
	fz(_r.l&0x08);
	_r.m=2;
	_r.t=8;
};

void z80::BIT3m(){
	fz(_mmu.rb((_r.h<<8)+_r.l)&0x08);
	_r.m=2;
	_r.t=8;
};

void z80::BIT4a(){
	fz(_r.a&0x10);
	_r.m=2;
	_r.t=8;
};

void z80::BIT4b(){
	fz(_r.b&0x10);
	_r.m=2;
	_r.t=8;
};

void z80::BIT4c(){
	fz(_r.c&0x10);
	_r.m=2;
	_r.t=8;
};

void z80::BIT4d(){
	fz(_r.d&0x10);
	_r.m=2;
	_r.t=8;
};

void z80::BIT4h(){
	fz(_r.h&0x10);
	_r.m=2;
	_r.t=8;
};

void z80::BIT4l(){
	fz(_r.l&0x10);
	_r.m=2;
	_r.t=8;
};

void z80::BIT4m(){
	fz(_mmu.rb((_r.h<<8)+_r.l)&0x10);
	_r.m=3;
	_r.t=12;
};

void z80::BIT5a(){
	fz(_r.a&0x20);
	_r.m=2;
	_r.t=8;
};

void z80::BIT5b(){
	fz(_r.b&0x20);
	_r.m=2;
	_r.t=8;
};

void z80::BIT5c(){
	fz(_r.c&0x20);
	_r.m=2;
	_r.t=8;
};

void z80::BIT5d(){
	fz(_r.d&0x20);
	_r.m=2;
	_r.t=8;
};

void z80::BIT5e(){
	fz(_r.e&0x20);
	_r.m=2;
	_r.t=8;
};

void z80::BIT5h(){
	fz(_r.l&0x20);
	_r.m=2;
	_r.t=8;
};

void z80::BIT5l(){
	fz(_r.l&0x20);
	_r.m=2;
	_r.t=8;
};

void z80::BIT5m(){
	fz(_mmu.rb((_r.h<<8)+_r.l)&0x20);
	_r.m=3;
	_r.t=12;
};

void z80::BIT6a(){
	fz(_r.a&0x40);
	_r.m=2;
	_r.t=8;
};

void z80::BIT6b(){
	fz(_r.b&0x40);
	_r.m=2;
	_r.t=8;
};

void z80::BIT6c(){
	fz(_r.c&0x40);
	_r.m=2;
	_r.t=8;
};

void z80::BIT6d(){
	fz(_r.d&0x40);
	_r.m=2;
	_r.t=8;
};


void z80::BIT6e(){
	fz(_r.e&0x40);
	_r.m=2;
	_r.t=8;
};

void z80::BIT6h(){
	fz(_r.l&0x40);
	_r.m=2;
	_r.t=8;
};

void z80::BIT6l(){
	fz(_r.l&0x40);
	_r.m=2;
	_r.t=8;
};

void z80::BIT6m(){
	fz(_mmu.rb((_r.h<<8)+_r.l)&0x40);
	_r.m=3;
	_r.t=12;
};

void z80::BIT7a(){
	fz(_r.a&0x80);
	_r.m=2;
	_r.t=8;
};

void z80::BIT7b(){
	fz(_r.b&0x80);
	_r.m=2;
	_r.t=8;
};

void z80::BIT7c(){
	fz(_r.c&0x80);
	_r.m=2;
	_r.t=8;
};

void z80::BIT7d(){
	fz(_r.d&0x80);
	_r.m=2;
	_r.t=8;
};

void z80::BIT7e(){
	fz(_r.e&0x80);
	_r.m=2;
	_r.t=8;
};

void z80::BIT7h(){
	fz(_r.a&0x80);
	_r.m=2;
	_r.t=8;
};

void z80::BIT7l(){
	fz(_r.a&0x80);
	_r.m=2;
	_r.t=8;
};

void z80::BIT7m(){
	fz(_mmu.rb((_r.h<<8)+_r.l)&0x80);
	_r.m=3;
	_r.t=12;
};

/*---------------------------*/

void z80::RLA(){
	 byte ci=_r.f&0x10?1:0;
	 byte co=_r.a&0x80?0x10:0;
	 _r.a=(_r.a<<1)+ci;
	 _r.a&=255;
	 _r.f=(_r.f&0xEF)+co;
	 _r.m=1;
	 _r.t=4;
};

void z80::RLCA(){
	byte ci=_r.a&0x80?1:0;
	byte co=_r.a&0x80?1:0;
	_r.a=(_r.a<<1)+ci;
	_r.a&=255;
	_r.f=(_r.f&0xEF)+co;
	_r.m=1;
	_r.t=4;
};

void z80::RRA(){
	byte ci=_r.f&0x10?0x80:0;
	byte co=_r.a&1?0x10:0;
	_r.a=(_r.a>>1)+ci;
	_r.a&=255;
	_r.f=(_r.f&0xEf)+co;
	_r.m=1;
	_r.t=4;
};

void z80::RRCA(){
	byte ci=_r.a&1?0x80:0;
	byte co=_r.a&1?0x10:0;
	_r.a=(_r.a>>1)+ci;
	_r.a&=255;
	_r.f=(_r.f&0xEF)+co;
	_r.m=1;
	_r.t=4;
};

void z80::RLr_a(){
	byte ci=_r.f&0x10?1:0;
	byte co=_r.a&0x80?0x10:0;
	_r.a=(_r.a<<1)+ci;
	_r.a&=255;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLr_b(){
	byte ci=_r.f&0x10?1:0;
	byte co=_r.b&0x80?0x10:0;
	_r.b=(_r.b<<1)+ci;
	_r.b&=255;
	fz(_r.b);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLr_c(){
	byte ci=_r.f&0x10?1:0;
	byte co=_r.c&0x80?0x10:0;
	_r.c=(_r.c<<1)+ci;
	_r.c&=255;
	fz(_r.c);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLr_d(){
	byte ci=_r.f&0x10?1:0;
	byte co=_r.d&0x80?0x10:0;
	_r.d=(_r.d<<1)+ci;
	_r.d&=255;
	fz(_r.d);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLr_e(){
	byte ci=_r.f&0x10?1:0;
	byte co=_r.e&0x80?0x10:0;
	_r.e=(_r.e<<1)+ci;
	_r.e&=255;
	fz(_r.e);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLr_h(){
	byte ci=_r.f&0x10?1:0;
	byte co=_r.h&0x80?0x10:0;
	_r.h=(_r.h<<1)+ci;
	_r.h&=255;
	fz(_r.h);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLr_l(){
	byte ci=_r.f&0x10?1:0;
	byte co=_r.l&0x80?0x10:0;
	_r.l=(_r.l<<1)+ci;
	_r.l&=255;
	fz(_r.l);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLHL(){
	byte i=_mmu.rb((_r.h<<8)+_r.l);
	byte ci=_r.f&0x10?1:0;
	byte co=i&0x80?0x10:0;
	i=(i<<1)+ci;
	i&=255;
	fz(i);
	_mmu.wb((_r.h<<8)+_r.l,i);
	_r.f=(_r.f&0xEF)+co;
	_r.m=4;
	_r.t=16;
};

/*---------------------------------*/

void z80::RLCr_a(){
	byte ci=_r.a&0x80?1:0;
	byte co=_r.a&0x80?0x10:0;
	_r.a=(_r.a<<1)+ci;
	_r.a&=255;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLCr_b(){
	byte ci=_r.b&0x80?1:0;
	byte co=_r.b&0x80?0x10:0;
	_r.b=(_r.b<<1)+ci;
	_r.b&=255;
	fz(_r.b);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLCr_c(){
	byte ci=_r.c&0x80?1:0;
	byte co=_r.c&0x80?0x10:0;
	_r.a=(_r.c<<1)+ci;
	_r.c&=255;
	fz(_r.c);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLCr_d(){
	byte ci=_r.d&0x80?1:0;
	byte co=_r.d&0x80?0x10:0;
	_r.d=(_r.d<<1)+ci;
	_r.d&=255;
	fz(_r.d);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLCr_e(){
	byte ci=_r.e&0x80?1:0;
	byte co=_r.e&0x80?0x10:0;
	_r.e=(_r.e<<1)+ci;
	_r.e&=255;
	fz(_r.e);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLCr_h(){
	byte ci=_r.h&0x80?1:0;
	byte co=_r.h&0x80?0x10:0;
	_r.h=(_r.h<<1)+ci;
	_r.h&=255;
	fz(_r.h);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLCr_l(){
	byte ci=_r.l&0x80?1:0;
	byte co=_r.l&0x80?0x10:0;
	_r.l=(_r.l<<1)+ci;
	_r.l&=255;
	fz(_r.l);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RLCHL(){
	byte i=_mmu.rb((_r.h<<8)+_r.l);
	byte ci=i&0x80?1:0;
	byte co=i&0x80?0x10:0;
	i=(i<<1)+ci;
	i&=255;
	fz(i);
	_mmu.wb((_r.h<<8)+_r.l,i);
	_r.f=(_r.f&0xEF)+co;
	_r.m=4;
	_r.t=16;
};

/*---------------------------------*/

void z80::RRr_a(){
	byte ci=_r.f&0x10?0x80:0;
	byte co=_r.a&1?0x10:0;
	_r.a=(_r.a>>1)+ci;
	_r.a&=255;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRr_b(){
	byte ci=_r.f&0x10?0x80:0;
	byte co=_r.b&1?0x10:0;
	_r.b=(_r.b>>1)+ci;
	_r.b&=255;
	fz(_r.b);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRr_c(){
	byte ci=_r.f&0x10?0x80:0;
	byte co=_r.c&1?0x10:0;
	_r.c=(_r.c>>1)+ci;
	_r.c&=255;
	fz(_r.c);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRr_d(){
	byte ci=_r.f&0x10?0x80:0;
	byte co=_r.d&1?0x10:0;
	_r.d=(_r.d>>1)+ci;
	_r.d&=255;
	fz(_r.d);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRr_e(){
	byte ci=_r.f&0x10?0x80:0;
	byte co=_r.e&1?0x10:0;
	_r.e=(_r.e>>1)+ci;
	_r.e&=255;
	fz(_r.e);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRr_h(){
	byte ci=_r.f&0x10?0x80:0;
	byte co=_r.h&1?0x10:0;
	_r.h=(_r.h>>1)+ci;
	_r.h&=255;
	fz(_r.h);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRr_l(){
	byte ci=_r.f&0x10?0x80:0;
	byte co=_r.l&1?0x10:0;
	_r.l=(_r.l>>1)+ci;
	_r.l&=255;
	fz(_r.l);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRHL(){
	byte i=_mmu.rb((_r.h<<8)+_r.l);
	byte ci=_r.f&0x10?0x80:0;
	byte co=i&1?0x10:0;
	i=(i>>1)+ci;
	i&=255;
	_mmu.wb((_r.h<<8)+_r.l,i);
	fz(i);
	_r.f=(_r.f&0xEF)+co;
	_r.m=4;
	_r.t=16;
};

/*----------------------------------------*/

void z80::RRCr_a(){
	byte ci = _r.a&1?0x80:0;
	byte co = _r.a&1?0x10:0;
	_r.a=(_r.a>>1)+ci;
	_r.a&=255;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};
void z80::RRCr_b(){
	byte ci = _r.b&1?0x80:0;
	byte co = _r.b&1?0x10:0;
	_r.b=(_r.b>>1)+ci;
	_r.b&=255;
	fz(_r.b);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRCr_c(){
	byte ci = _r.c&1?0x80:0;
	byte co = _r.c&1?0x10:0;
	_r.c=(_r.c>>1)+ci;
	_r.c&=255;
	fz(_r.c);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRCr_d(){
	byte ci = _r.d&1?0x80:0;
	byte co = _r.d&1?0x10:0;
	_r.d=(_r.d>>1)+ci;
	_r.d&=255;
	fz(_r.d);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRCr_e(){
	byte ci = _r.e&1?0x80:0;
	byte co = _r.e&1?0x10:0;
	_r.e=(_r.e>>1)+ci;
	_r.e&=255;
	fz(_r.e);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRCr_h(){
	byte ci = _r.h&1?0x80:0;
	byte co = _r.h&1?0x10:0;
	_r.h=(_r.h>>1)+ci;
	_r.h&=255;
	fz(_r.h);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRCr_l(){
	byte ci = _r.l&1?0x80:0;
	byte co = _r.l&1?0x10:0;
	_r.l=(_r.l>>1)+ci;
	_r.l&=255;
	fz(_r.l);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::RRCHL(){
	byte i=_mmu.rb((_r.h<<8)+_r.l);
	byte ci = i&1?0x80:0;
	byte co = i&1?0x10:0;
	i=(i>>1)+ci;
	i&=255;
	_mmu.wb((_r.h<<8)+_r.l,i);
	fz(i);
	_r.f=(_r.f&0xEF)+co;
	_r.m=4;
	_r.t=16;
};

/*---------------------------------*/

void z80::SLAr_a(){
	byte co = _r.a&0x80?0x10:0;
	_r.a=(_r.a<<1)&255;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLAr_b(){
	byte co = _r.b&0x80?0x10:0;
	_r.b=(_r.b<<1)&255;
	fz(_r.b);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLAr_c(){
	byte co = _r.c&0x80?0x10:0;
	_r.c=(_r.c<<1)&255;
	fz(_r.c);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLAr_d(){
	byte co = _r.d&0x80?0x10:0;
	_r.d=(_r.d<<1)&255;
	fz(_r.d);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLAr_e(){
	byte co = _r.e&0x80?0x10:0;
	_r.e=(_r.e<<1)&255;
	fz(_r.e);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLAr_h(){
	byte co = _r.h&0x80?0x10:0;
	_r.h=(_r.h<<1)&255;
	fz(_r.h);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLAr_l(){
	byte co = _r.l&0x80?0x10:0;
	_r.l=(_r.l<<1)&255;
	fz(_r.l);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

/*------------------------------------*/

void z80::SLLr_a(){
	byte co = _r.a&0x80?0x10:0;
	_r.a=(_r.a<<1)&255+1;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLLr_b(){
	byte co = _r.b&0x80?0x10:0;
	_r.b=(_r.b<<1)&255+1;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLLr_c(){
	byte co = _r.c&0x80?0x10:0;
	_r.c=(_r.c<<1)&255+1;
	fz(_r.c);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLLr_d(){
	byte co = _r.d&0x80?0x10:0;
	_r.d=(_r.d<<1)&255+1;
	fz(_r.d);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLLr_e(){
	byte co = _r.e&0x80?0x10:0;
	_r.e=(_r.e<<1)&255+1;
	fz(_r.e);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLLr_h(){
	byte co = _r.h&0x80?0x10:0;
	_r.h=(_r.h<<1)&255+1;
	fz(_r.h);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SLLr_l(){
	byte co = _r.l&0x80?0x10:0;
	_r.l=(_r.l<<1)&255+1;
	fz(_r.l);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

/*--------------------------------*/

void z80::SRAr_a(){
	byte ci = _r.a&0x80;
	byte co = _r.a&1?0x10:0;
	_r.a=((_r.a>>1)+ci)&255;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRAr_b(){
	byte ci = _r.b&0x80;
	byte co = _r.b&1?0x10:0;
	_r.b=((_r.b>>1)+ci)&255;
	fz(_r.b);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRAr_c(){
	byte ci = _r.c&0x80;
	byte co = _r.c&1?0x10:0;
	_r.c=((_r.c>>1)+ci)&255;
	fz(_r.c);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRAr_d(){
	byte ci = _r.d&0x80;
	byte co = _r.d&1?0x10:0;
	_r.d=((_r.d>>1)+ci)&255;
	fz(_r.d);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRAr_e(){
	byte ci = _r.e&0x80;
	byte co = _r.e&1?0x10:0;
	_r.e=((_r.e>>1)+ci)&255;
	fz(_r.e);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRAr_h(){
	byte ci = _r.h&0x80;
	byte co = _r.h&1?0x10:0;
	_r.h=((_r.h>>1)+ci)&255;
	fz(_r.h);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRAr_l(){
	byte ci = _r.l&0x80;
	byte co = _r.l&1?0x10:0;
	_r.l=((_r.l>>1)+ci)&255;
	fz(_r.l);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

/*-------------------------------*/


void z80::SRLr_a(){
	byte co = _r.a&1?0x10:0; 
	_r.a=(_r.a>>1)&255;
	fz(_r.a);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRLr_b(){
	byte co = _r.b&1?0x10:0; 
	_r.b=(_r.b>>1)&255;
	fz(_r.b);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRLr_c(){
	byte co = _r.c&1?0x10:0; 
	_r.c=(_r.c>>1)&255;
	fz(_r.c);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRLr_d(){
	byte co = _r.d&1?0x10:0; 
	_r.d=(_r.d>>1)&255;
	fz(_r.d);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRLr_e(){
	byte co = _r.e&1?0x10:0; 
	_r.e=(_r.e>>1)&255;
	fz(_r.e);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRLr_h(){
	byte co = _r.h&1?0x10:0; 
	_r.h=(_r.h>>1)&255;
	fz(_r.h);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

void z80::SRLr_l(){
	byte co = _r.l&1?0x10:0; 
	_r.l=(_r.l>>1)&255;
	fz(_r.l);
	_r.f=(_r.f&0xEF)+co;
	_r.m=2;
	_r.t=8;
};

/*--------------------------------*/

void z80::CPL(){
	_r.a=(~_r.a)&255;
	fz(_r.a,1);
	_r.m=1;
	_r.t=4;
};

void z80::NEG(){
	_r.a=0-_r.a;
	fz(_r.a,1);
	if(_r.a<0)_r.f|=0x10;
	_r.a&=255;
	_r.m=2;
	_r.t=8;
};

void z80::CCF(){
	byte ci=_r.f&0x10?0:0x10;
	_r.f=(_r.f&0xEF)+ci;
	_r.m=1;
	_r.t=4;
};

void z80::SCF(){
	_r.f|=0x10;
	_r.m=1;
	_r.t=4;
};

/*------------------Stack-----------------------*/

void z80::PUSHBC(){
	_r.sp--;
	_mmu.wb(_r.sp,_r.b);
	_r.sp--;
	_mmu.wb(_r.sp,_r.c);
	_r.m=3;
	_r.t=12;
};

void z80::PUSHDE(){
	_r.sp--;
	_mmu.wb(_r.sp,_r.d);
	_r.sp--;
	_mmu.wb(_r.sp,_r.e);
	_r.m=3;
	_r.t=12;
};

void z80::PUSHHL(){
	_r.sp--;
	_mmu.wb(_r.sp,_r.h);
	_r.sp--;
	_mmu.wb(_r.sp,_r.l);
	_r.m=3;
	_r.t=12;
};

void z80::PUSHAF(){
	_r.sp--;
	_mmu.wb(_r.sp,_r.a);
	_r.sp--;
	_mmu.wb(_r.sp,_r.f);
	_r.m=3;
	_r.t=12;
};

void z80::POPBC(){
	_r.c=_mmu.rb(_r.sp);
	_r.sp++;
	_r.b=_mmu.rb(_r.sp);
	_r.sp++;
	_r.m=3;
	_r.t=12;
};

void z80::POPDE(){
	_r.e=_mmu.rb(_r.sp);
	_r.sp++;
	_r.d=_mmu.rb(_r.sp);
	_r.sp++;
	_r.m=3;
	_r.t=12;
};
	

void z80::POPHL(){
	_r.l=_mmu.rb(_r.sp);
	_r.sp++;
	_r.h=_mmu.rb(_r.sp);
	_r.sp++;
	_r.m=3;
	_r.t=12;
};

void z80::POPAF(){
	_r.f=_mmu.rb(_r.sp);
	_r.sp++;
	_r.a=_mmu.rb(_r.sp);
	_r.sp++;
	_r.m=3;
	_r.t=12;
};

/*--------------------Jump-------------------------*/

void z80::JPnn(){
	_r.pc=_mmu.rw(_r.pc);
	_r.m=3;
	_r.t=12;
};

void z80::JPHL(){
	_r.pc=_mmu.rw((_r.h<<8)+_r.l);
	_r.m=1;
	_r.t=4;
};

void z80::JPNZnn(){
	_r.m=3;
	_r.t=12;
	if((_r.f&0x80)==0x00)
	{
		_r.pc=_mmu.rw(_r.pc);
		_r.m++;
		_r.t+=4;
	}
	else
		 _r.pc+=2;
};

void z80::JPZnn(){
	_r.m=3;
	_r.t=12;
	if((_r.f&0x80)==0x80)
	{
		_r.pc=_mmu.rw(_r.pc);
		_r.m++;
		_r.t+=4;
	}
	else
		 _r.pc+=2;
};

void z80::JPNCnn(){
	_r.m=3;
	_r.t=12;
	if((_r.f&0x10)==0x00)
	{
		_r.pc=_mmu.rw(_r.pc);
		_r.m++;
		_r.t+=4;
	}
	else
		 _r.pc+=2;
};

void z80::JPCnn(){
	_r.m=3;
	_r.t=12;
	if((_r.f&0x10)==0x10)
	{
		_r.pc=_mmu.rw(_r.pc);
		_r.m++;
		_r.t+=4;
	}
	else
		 _r.pc+=2;
};


void z80::JRn(){
	byte i=_mmu.rb(_r.pc);
	if(i>127)i=-((~i+1)&255);
	_r.pc++;
	_r.m=2;
	_r.t=8;
	_r.pc+=i;
	_r.m++;
	_r.t+=4;
};

void z80::JRNZn(){
	byte i=_mmu.rb(_r.pc);
	if(i>127)i=-((~i+1)&255);
	_r.pc++;
	_r.m=2;
	_r.t=8;
	if((_r.f&0x80)==0x00)
	{
		_r.pc+=i;
		_r.m++;
		_r.t+=4;
	}
};

void z80::JRZn(){
	byte i=_mmu.rb(_r.pc);
	if(i>127)i=-((~i+1)&255);
	_r.pc++;
	_r.m=2;
	_r.t=8;
	if((_r.f&0x80)==0x80)
	{
		_r.pc+=i;
		_r.m++;
		_r.t+=4;
	}
};

void z80::JRNCn(){
	byte i=_mmu.rb(_r.pc);
	if(i>127)i=-((~i+1)&255);
	_r.pc++;
	_r.m=2;
	_r.t=8;
	if((_r.f&0x10)==0x00)
	{
		_r.pc+=i;
		_r.m++;
		_r.t+=4;
	}
};

void z80::JRCn(){
	byte i=_mmu.rb(_r.pc);
	if(i>127)i=-((~i+1)&255);
	_r.pc++;
	_r.m=2;
	_r.t=8;
	if((_r.f&0x10)==0x10)
	{
		_r.pc+=i;
		_r.m++;
		_r.t+=4;
	}
};

void z80::DJNZn(){
	byte i=_mmu.rb(_r.pc);
	if(i>127)i=((~i+1)&255);
	_r.pc++;
	_r.m=2;
	_r.t=8;
	_r.b--;
	if(_r.b)
	{
		_r.pc+=i;
		_r.m++;
		_r.t+=4;
	}
};


void z80::CALLnn(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc+2);
	_r.pc=_mmu.rw(_r.pc);
	_r.m=5;
	_r.t=20;
};

void z80::CALLNZnn(){
	_r.m=3;
	_r.t=12;
	if((_r.f&0x80)==0x00)
	{
		_r.sp-=2;
		_mmu.ww(_r.sp,_r.pc+2);
		_r.pc=_mmu.rw(_r.pc);
		_r.m+=2;
		_r.t+=8;
	}
	else
		_r.pc+=2;
};

void z80::CALLZnn(){
	_r.m=3;
	_r.t=12;
	if((_r.f&0x80)==0x80)
	{
		_r.sp-=2;
		_mmu.ww(_r.sp,_r.pc+2);
		_r.pc=_mmu.rw(_r.pc);
		_r.m+=2;
		_r.t+=8;
	}
	else
		_r.pc+=2;
};

void z80::CAllNCnn(){
	_r.m=3;
	_r.t=12;
	if((_r.f&0x10)==0x00)
	{
		_r.sp-=2;
		_mmu.ww(_r.sp,_r.pc+2);
		_r.pc=_mmu.rw(_r.pc);
		_r.m+=2;
		_r.t+=8;
	}
	else
		_r.pc+=2;
};

void z80::CALLCnn(){
	_r.m=3;
	_r.t=12;
	if((_r.f&0x10)==0x10)
	{
		_r.sp-=2;
		_mmu.ww(_r.sp,_r.pc+2);
		_r.pc=_mmu.rw(_r.pc);
		_r.m+=2;
		_r.t+=8;
	}
	else
		_r.pc+=2;
};

void z80::RET(){
	_r.pc=_mmu.rw(_r.sp);
	_r.sp+=2;
	_r.m=3;
	_r.t=12;
};

void z80::RETI(){
	_r.ime=1;
	_r.pc=_mmu.rw(_r.sp);
	_r.sp+=2;
	_r.m=3;
	_r.t=12;
};

void z80::RETNZ(){
	_r.m=1;
	_r.t=4;
	if((_r.f&0x80)==0x00)
	{
		_r.pc=_mmu.rw(_r.sp);
		_r.sp+=2;
		_r.m+=2;
		_r.t+=8;
	}
};

void z80::RETZ(){
	_r.m=1;
	_r.t=4;
	if((_r.f&0x80)==0x80)
	{
		_r.pc=_mmu.rw(_r.sp);
		_r.sp+=2;
		_r.m+=2;
		_r.t+=8;
	}
};

void z80::RETNC(){
    _r.m=1;
	_r.t=4;
	if((_r.f&0x10)==0x00)
	{
		_r.pc=_mmu.rw(_r.sp);
		_r.sp+=2;
		_r.m+=2;
		_r.t+=8;
	}
};

void z80::RETC(){
	_r.m=1;
	_r.t=4;
	if((_r.f&0x10)==0x10)
	{
		_r.pc=_mmu.rw(_r.sp);
		_r.sp+=2;
		_r.m+=2;
		_r.t+=8;
	}
};

void z80::RST00(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x00;
	_r.m=3;
	_r.t=12;
};

void z80::RST08(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x08;
	_r.m=3;
	_r.t=12;
};

void z80::RST10(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x10;
	_r.m=3;
	_r.t=12;
};

void z80::RST18(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x18;
	_r.m=3;
	_r.t=12;
};

void z80::RST20(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x20;
	_r.m=3;
	_r.t=12;
};

void z80::RST28(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x28;
	_r.m=3;
	_r.t=12;
};

void z80::RST30(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x30;
	_r.m=3;
	_r.t=12;
};

void z80::RST38(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x38;
	_r.m=3;
	_r.t=12;
};

void z80::RST40(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x40;
	_r.m=3;
	_r.t=12;
};

void z80::RST48(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x00;
	_r.m=3;
	_r.t=12;
};

void z80::RST50(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x50;
	_r.m=3;
	_r.t=12;
};

void z80::RST58(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x58;
	_r.m=3;
	_r.t=12;
};

void z80::RST60(){
	_r.sp-=2;
	_mmu.ww(_r.sp,_r.pc);
	_r.pc=0x60;
	_r.m=3;
	_r.t=12;
};

/*----------------------------------------*/

void z80::HALT(){
	_halt=1;
	_r.m=1;
	_r.t=4;
};

void z80::DI(){
	_r.ime=0;
	_r.m=1;
	_r.t=4;
};

void z80::EI(){
	_r.ime=1;
	_r.m=1;
	_r.t=4;
};

void z80::NOP(){
	_r.m=1;
	_r.t=4;  // this function simulates the NOP instruction. do nothing here.
};


void z80::print_status(){
	printf("The amount of CPU clock M was %d\n",_clock.m);
	printf("The amount of CPU clock T was %d\n",_clock.t);
	printf("The amount of register a was %d\n",_r.a);
	printf("The amount of register b was %d\n",_r.b);
	printf("The amount of register c was %d\n",_r.c);
	printf("The amount of register d was %d\n",_r.d);
	printf("The amount of register e was %d\n",_r.e);
	printf("The amount of register h was %d\n",_r.h);
	printf("The amount of register l was %d\n",_r.l);
	printf("The amount of register m was %d\n",_r.m);
	printf("The amount of register t was %d\n",_r.t);
};

void z80::XX(){};
void z80::fz(byte i){};
void z80::fz(byte i,byte as){};
void z80::MAPcb(){};

void z80::reset(){
	_clock.m=0;
	_clock.t=0;
	_r.a=0;
	_r.b=0;
	_r.c=0;
	_r.d=0;
	_r.e=0;
	_r.f=0;
	_r.h=0;
	_r.l=0;
	_r.m=0;
	_r.t=0; 
	_r.sp=0;
	_r.pc=0;  //reset all the registers to 0;
	
};




int _tmain(int argc, _TCHAR* argv[])
{
	z80 core=z80();
	(core.*core._map[0])();
	int t=getchar();
	return 0;
}

