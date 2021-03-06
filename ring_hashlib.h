unsigned       ring_hash(unsigned pid);
unsigned       ring_add_hash(unsigned char* key,int len);
unsigned       ring_xor_hash(unsigned char* key,int len);
unsigned       ring_rot_hash(unsigned char* key,int len);
unsigned       ring_djb_hash(unsigned char* key,int len);
unsigned       ring_sax_hash(unsigned char* key,int len);
unsigned       ring_fnv_hash(unsigned char* key,int len);
unsigned       ring_oat_hash(unsigned char* key,int len);
unsigned       ring_elf_hash(unsigned char* key,int len);
unsigned       ring_jen_hash(unsigned char* k,unsigned length,unsigned initval);
unsigned int   ring_murmur3_32(const char* key,unsigned int len,unsigned int seed);

/* ******************************************************************** **
** @@                   The End
** ******************************************************************** */
