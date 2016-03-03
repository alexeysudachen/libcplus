TOPDIR = ..
SRCDIR = .
PROJECT=test_crypto

!INCLUDE $(XTERNAL)\Make.rules.mak

INCL = -I $(TOPDIR)\.. -I $(SRCDIR)
CFLAGS = $(CFLAGS) -D_THREADS -D_BUILTIN

TESTS = \
    $(TSTDIR)\sha1.exe \
    $(TSTDIR)\hmacsha1.exe \
    $(TSTDIR)\bigint.exe \
    $(TSTDIR)\bigint.txt \

_TESTS = \
    $(BINDIR)\md5.exe \
    $(BINDIR)\sha1.exe \
    $(BINDIR)\sha2.exe \
    $(BINDIR)\hmacmd5.exe \
    $(BINDIR)\hmacsha1.exe \
    $(BINDIR)\hmacsha2.exe \
    $(BINDIR)\random.exe \
    $(BINDIR)\aes.exe \
    $(BINDIR)\blowfish.exe \
    $(BINDIR)\rsa.exe \
    $(BINDIR)\rsagen.exe \
    $(BINDIR)\prime.exe \
    $(BINDIR)\modpow2.exe \

!INCLUDE $(XTERNAL)\Make.tests.mak



