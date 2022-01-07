# build configuration for autotools
#
# autoconf setup:
# [projekt name], [version], [bug report adress]
AC_INIT([tgwatcher], [0.0.1])

# safety check in case user overwritten --srcdir
AC_CONFIG_SRCDIR([configure.ac])

AC_CONFIG_AUX_DIR([autotools])

# Init automake with relaxed structures:
# ChangeLog, COPYING, AUTHORS, INSTALL, README etc. are not required
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])


# Check for C compiler
AC_PROG_CC

# Tells automake to create a Makefile
# See https://www.gnu.org/software/automake/manual/html_node/Requirements.html
AC_CONFIG_FILES([Makefile])

AC_OUTPUT

