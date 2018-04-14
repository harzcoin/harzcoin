#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

HARZCOIND=${HARZCOIND:-$SRCDIR/harzcoind}
HARZCOINCLI=${HARZCOINCLI:-$SRCDIR/harzcoin-cli}
HARZCOINTX=${HARZCOINTX:-$SRCDIR/harzcoin-tx}
HARZCOINQT=${HARZCOINQT:-$SRCDIR/qt/harzcoin-qt}

[ ! -x $HARZCOIND ] && echo "$HARZCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
THALERVER=($($HARZCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for harzcoind if --version-string is not set,
# but has different outcomes for harzcoin-qt and harzcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$HARZCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $HARZCOIND $HARZCOINCLI $HARZCOINTX $HARZCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${THALERVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${THALERVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
