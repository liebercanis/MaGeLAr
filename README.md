# MaGeLAr
MaGe with output for liquid argon veto

adds LTree to MaGe root output
Special instructions for installing LTree library 
ln -s  $MAGEDIR/lib/libLegendRoot.so  $MGDODIR/lib/

in  $MAGEDIR/buildTools/mgbin.mk add line
	MGBINLIBS += -L$(MAGEDIR)/io/obj/ -lLegendRoot

directory for LegendRoot library is $MAGEDIR/io/obj
in io/obj
	> make
	> make install

copies library to $MAGEDIR/lib/libLegendRoot.so 
