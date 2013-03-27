
#include "stdafx.h"
#include "MMU.h"
MMU::MMU(){};
byte MMU::rb(byte addr){
	
	switch(addr&0xF000){
		//ROM Bank 0
	case 0x0000:
		if(_inbios){
			if(addr<0x0100)return _bios[addr];
			else if(_pc==0x0100)
			{
				_inbios =0;
			}
		}
		else return _rom[addr];

	case 0x1000:
	case 0x2000:
	case 0x3000: return _rom[addr];

		//ROM bank 1
	case 0x4000:
	case 0x5000:
	case 0x6000:
	case 0x7000: return _rom[_romoffs+(addr&0x3FFF)];

		//VRAM
	case 0x8000: 
	case 0x9000:return 42;  //GPU._vram[addr&0x1FFF];

		//External RAM
	case 0xA000:
	case 0xB000: return _eram[_ramoffs+(addr&0x1FFF)];

		//Work RAM and echo
	case 0xC000:
	case 0xD000:
	case 0xE000:
		return _wram[addr&0x1FFF];

		//everything else 
	case 0xF000:
		switch(addr&0x0F00)
		{
			 //Echo RAM
		case 0x000:
		case 0x100:
		case 0x200:
		case 0x300:
		case 0x400:
		case 0x500:
		case 0x600:
		case 0x700:
		case 0x800:
		case 0x900:
		case 0xA00:
		case 0xB00:
		case 0xC00:
		case 0xD00:return _wram[addr&0x1FFF];

			//OAM
		case 0xE00:return ((addr&0xFF)<0xA0)?1:0; // GPU.oam[addr&0xFF]:0;
			//Zeropage RAM I/O interruputs
		case 0xF00:
			if(addr==0xFFFF)return _ie;
			else if(addr>0xFF7F)return _zram[addr&0x7F];
			else switch (addr&0xF0)
			{
			case 0x00:
					switch (addr&0xF)
					{
					case 0:
							return 42; //JOYP  KEY.rb();
					case 4:
					case 5:
					case 6:
					case 7:
							return 42; //TIMER.rb(addr);
					case 15:
							return _if;
					default:
							return 0;

					}
			case 0x10:
			case 0x20:
			case 0x30:
					return 0;
			case 0x40:
			case 0x50:
			case 0x60:
			case 0x70:
					return 42; //GPU.rb(addr);
			}
		}
}

};

byte MMU::rw(byte addr){
	
	return rb(addr)+(rb(addr+1)<<8);
};
void MMU::wb(byte addr,byte val){
	switch(addr&0xF000)
	{
	//ROM bank 0
	//MBC1: Turn external RAM on
	case 0x0000:
	case 0x1000:
			switch (_carttype)
			{
			case 1:
				//_mbc[1].ramon=((val&0xF)==0xA)?1:0;
				break;
			}
			
			//MBC1:ROM bank switch 
	case 0x2000:
	case 0x3000:
		switch(_carttype)
		{
		case 1:
			//_mbc[1].rombank &=0x60;
			val &= 0x1F;
			if(!val)val=-1;
			//_mbc[1].rombank|=val;
			//_romoffs=_mbc[1].rombank*0x4000;
			break;
		}
		break;

		//ROM bank 1
		//MBC1: RAM bank switch
	case 0x4000:
	case 0x5000:
		switch(_carttype)
		{
		case 1:
			if(1)//_mbc[1].mode
			{
				//_mbc[1].rambank=(val&3);
			//	_ramoffs=_mbc[1].rambank*0x2000;
			}
			
			else 
			{
				//_mbc[1].rombank&=0x1F;
				//_mbc[1].rombank|=((val&3)<<5);
				//_romoffs=_mbc[1].rombank*0x4000;
			}
			break;

		case  0x6000:
		case  0x7000:
				switch(_carttype)
				{
				case 1:
					//_mbc[1].mode = val&1;
					break;
				}
				break;

				//VRAM
		case 0x8000:
		case 0x9000:
			//GPU._vram[addr&0x1FFF]=val;
			//GPU.updatetile(addr&0x1FFF,val);
			break;

			//external RAM
		case 0xA000:
		case 0xB000:
			_eram[_ramoffs+(addr&0x1FFF)]=val;
			break;

			//Work RAM and echo

		case 0xC000:
		case 0xD000:
		case 0xE000:
					_wram[addr&0x1FFF]=val;
					break;

					//Everything else

		case 0xF000:
			switch(addr&0x0F00)
			{
				//Echo 
			case 0x000:
			case 0x100:
			case 0x200:
			case 0x300:
			case 0x400:
			case 0x500:
			case 0x600:
			case 0x700:
			case 0x800:
			case 0x900:
			case 0xA00:
			case 0xB00:
			case 0xC00:
			case 0xD00:
						_wram[addr&0x1FFF]=val;
						break;

						//OAM
			case 0xE00:
					if((addr&0xFF)<0xA0)//GPU.oam[addr&0xFF]=val
						//GPU.updateoam(addr,val);
						break;
					//zeropage RAM ,I/O,interrupts
			case 0xF00:
				if(addr==0xFFFF){_ie=val;}
				else if(addr>0xFF7F)_zram[addr&0x7F]=val;
				else switch (addr&0xF0)
				{
				case 0x00:
						switch(addr&0xF)
						{
							case 0:
								  //KEY.wb(val);
									break;
							case 4:
							case 5:
							case 6:
							case 7:
								//TIMER.wb(addr,val);
									break;
							case 15:
									_if=val;
									break;

						}
						break;
						
				case 0x10:
				case 0x20:
				case 0x30:
							break;
				case 0x40:
				case 0x50:
				case 0x60:
				case 0x70:
							//GPU.wb(addr,val);
					break;
				}

			}
			break;
			}
			}



};

void MMU::ww(byte addr,byte val){ 
			wb(addr,val&255);
			wb(addr+1,val>>8);

};


void MMU::reset(){
		int i;
		for(i=0;i<127;i++)_zram[i]=0;
		for(i=0;i<8192;i++)_wram[i]=0;
		for(i=0;i<32768;i++)_eram[i]=0;
		_inbios=1;
		_ie=0;
		_if=0;
		_carttype=0;
};