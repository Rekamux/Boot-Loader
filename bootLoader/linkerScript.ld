MEMORY
{
  flash (rx) : org = 0x00000000, len = 2M
  void (rx) : org = 0x0D000000, len = 0M
}

SECTIONS
{
  .startup :
  {
    crt0.o(.text)
  } > flash

  .text :
  {
    *(.text)
  } > flash

  .rodata :
  {
    *(*rodata*)
  } > flash

  .data :
  {
    *(.data)
  } > void

  .bss :
  {
    *(.bss)
  } > void
}

