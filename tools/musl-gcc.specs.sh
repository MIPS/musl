incdir=$1
libdir=$2
ldso=$3
cat <<EOF
%rename cpp_options old_cpp_options

*cpp_options:
-nostdinc -isystem $incdir -isystem include%s -D__linux__ %(old_cpp_options)

*cc1:
%(cc1_cpu) -mel -nostdinc -isystem $incdir -isystem include%s -D__linux__ -msoft-float -fno-builtin

*link_libgcc:
-L$libdir -L .%s

*libgcc:
libgcc.a%s %:if-exists(libgcc_eh.a%s)

*lib:
-lc

*startfile:
%{!shared: $libdir/%{pie:S}crt1.o} $libdir/crti.o

*endfile:
$libdir/crtn.o

*link:
-melf32ltsmip -msoft-float -dynamic-linker $ldso -nostdlib %{shared:-shared} %{static:-static} %{rdynamic:-export-dynamic}

*esp_link:


*esp_options:


*esp_cpp_options:


EOF
