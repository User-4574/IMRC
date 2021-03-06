#!perl
use Config;
use File::Copy;
if ($^O eq 'MSWin32')
 {
  my $file;
  chmod(0666,'Makefile');
  chmod(0666,'jconfig.h');
  if ($Config{'cc'} =~ /gcc/)
   {
    copy("jconfig.v32","jconfig.h") ||
     die "Cannot copy jconfig.v32 to jconfig.h:$!";
    $file = 'makefile.mingw32';
   }
  elsif ($Config{'cc'} =~ /bcc/)
   {
    copy("jconfig.b32","jconfig.h") ||
     die "Cannot copy jconfig.b32 to jconfig.h:$!";
    $file = 'makefile.b32';
   }
  else
   {
    copy("jconfig.v32","jconfig.h") ||
     die "Cannot copy jconfig.v32 to jconfig.h:$!";
    $file = 'makefile.v32';
    warn "Assuming ".$Config{'cc'}." is visual C of some kind\n";
   }
  copy($file,"Makefile")
   || die "Cannot copy $file to Makefile:$!";
 }
else
 {
  $ENV{CC} = $Config{cc};
  local $ENV{CFLAGS} = "$Config{ccflags} $Config{cccdlflags}";
  local $ENV{LDFLAGS} = "$Config{ccflags} $Config{ldflags}";
  system(sh => "./configure");
 }
1;
