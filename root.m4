dnl -*- mode: autoconf -*- 
dnl
dnl Autoconf macro to check for existence of ROOT on the system
dnl Synopsis:
dnl
dnl  ROOT_PATH([MINIMUM-VERSION, [ACTION-IF-FOUND, [ACTION-IF-NOT-FOUND]]])
dnl
dnl Some examples: 
dnl 
dnl    ROOT_PATH(3.03/05, , AC_MSG_ERROR(Your ROOT version is too old))
dnl    ROOT_PATH(, AC_DEFUN(HAVE_ROOT))
dnl 
dnl The macro defines the following substitution variables
dnl
dnl    ROOTCONF           full path to root-config
dnl    ROOTEXEC           full path to root
dnl    ROOTCINT           full path to rootcint
dnl    ROOTCLING          full path to rootcling
dnl    RLIBMAP            full path to rlibmap
dnl    ROOTLIBDIR         Where the ROOT libraries are 
dnl    ROOTINCDIR         Where the ROOT headers are 
dnl    ROOTCFLAGS         Extra compiler flags
dnl    ROOTLIBS           ROOT basic libraries 
dnl    ROOTGLIBS          ROOT basic + GUI libraries
dnl    ROOTAUXLIBS        Auxilary libraries and linker flags for ROOT
dnl    ROOTAUXCFLAGS      Auxilary compiler flags 
dnl    ROOTRPATH          Same as ROOTLIBDIR
dnl
dnl The macro will fail if root-config, rootcint or rlibmap isn't found.
dnl
dnl Original version by Christian Holm Christensen <cholm@nbi.dk>
dnl

AC_DEFUN([ROOT_PATH],
[
  AC_ARG_WITH(rootsys,
  [  --with-rootsys          top of the ROOT installation directory],
    user_rootsys=$withval,
    user_rootsys="none")
  if test ! x"$user_rootsys" = xnone; then
    rootbin="$user_rootsys/bin"
  elif test ! x"$ROOTSYS" = x ; then 
    rootbin="$ROOTSYS/bin"
  else 
   rootbin=$PATH
  fi
  AC_PATH_PROG(ROOTCONF, root-config , no, $rootbin)
  AC_PATH_PROG(ROOTEXEC, root , no, $rootbin)
  AC_PATH_PROG(ROOTCINT, rootcint , no, $rootbin)
  AC_PATH_PROG(ROOTCLING, rootcling, false, $rootbin)
  AC_PATH_PROG(RLIBMAP, rlibmap, false, $rootbin)

  if test "${ROOTCLING}" = false -a "${RLIBMAP}" = false; then
    AC_MSG_ERROR([Need rootcling (ROOT-6) or rlibmap (ROOT-5).]);
  fi

  if test ! x"$ROOTCONF" = "xno" && \
     test ! x"$ROOTCINT" = "xno" && \
     test ! x"$ROOTCLING" = "xno" && \
     test ! x"$RLIBMAP" = "xno" ; then 

	# Set ROOTSYS, if not already set
	if test x"$ROOTSYS" = x ; then 
      ROOTSYS=`$ROOTCONF --prefix`
    fi

	 # define some variables 
    ROOTLIBDIR=`$ROOTCONF --libdir`
    ROOTINCDIR=`$ROOTCONF --incdir`
    ROOTCFLAGS=`$ROOTCONF --noauxcflags --cflags` 
    ROOTLIBS=`$ROOTCONF --noauxlibs --noldflags --libs`
    ROOTGLIBS=`$ROOTCONF --noauxlibs --noldflags --glibs`
    ROOTAUXCFLAGS=`$ROOTCONF --auxcflags`
    ROOTAUXLIBS=`$ROOTCONF --auxlibs`
    ROOTRPATH=$ROOTLIBDIR
	
    if test $1 ; then 
      AC_MSG_CHECKING(whether ROOT version >= [$1])
      vers=`$ROOTCONF --version | tr './' ' ' | awk 'BEGIN { FS = " "; } { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
      requ=`echo $1 | tr './' ' ' | awk 'BEGIN { FS = " "; } { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
      if test $vers -lt $requ ; then 
        AC_MSG_RESULT(no)
	no_root="yes"
      else 
        AC_MSG_RESULT(yes)
      fi
    fi
  else
    # otherwise, we say no_root
    no_root="yes"
  fi

  AC_SUBST(ROOTSYS)
  AC_SUBST(ROOTLIBDIR)
  AC_SUBST(ROOTINCDIR)
  AC_SUBST(ROOTCFLAGS)
  AC_SUBST(ROOTLIBS)
  AC_SUBST(ROOTGLIBS) 
  AC_SUBST(ROOTAUXLIBS)
  AC_SUBST(ROOTAUXCFLAGS)
  AC_SUBST(ROOTRPATH)

  if test "x$no_root" = "x" ; then 
    ifelse([$2], , :, [$2])     
  else 
    ifelse([$3], , :, [$3])     
  fi
])


#
# EOF
#
