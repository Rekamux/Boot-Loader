MEMORY
{
  ram (wx)   : org = 0x0C000000, len = 8M
}

SECTIONS
{
  .startup :
  {
    crt0.o(.text)
  } > ram

  .text :
  {
    *(.text)
  } > ram

  .rodata :
  {
    *(*rodata*)
  } > ram

  .data :
  {
    *(.data)
  } > ram

  .bss :
  {
    __start_bss = .;
    *(.bss)
    __end_bss = .;
  } > ram
}

