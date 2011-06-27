MEMORY
{
  flash (rx) : org = 0x00003000, len = 2M
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

  partition_begin = .;
  .partition :
  {
    partition.o(.data)
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

