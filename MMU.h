
// Memory Management unit

typedef unsigned short byte; // two bytes for store to address addr(also two bytes) 
typedef unsigned short addr;
typedef unsigned short word;

class MMU{
public:
	byte rb(addr address);  // read one byte from the address
    byte rw(addr address);  // read one word from the address 
	byte wb(addr address,byte val);  // write one byte into the address
	byte ww(addr address,byte val); //write one word into the address-/

};