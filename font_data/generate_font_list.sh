#!/bin/sh

font_name() {
	cat "${1}" | grep Family | sed -e 's/.*Family: \(.*\)$/\1/'
}
font_size() {
	cat "${1}" | grep Size | sed -e 's/.*Size: \(.*\)$/\1/'
}


rm -f font_list.h
rm -f font_list.c
fonts="$(ls *.h)"
exec 4>&1
exec 3<> font_list.h
exec 1>&3
echo "#ifndef __FONT_LIST_H"
echo "#define __FONT_LIST_H"
echo ""
echo "#include \"font_info.h\""
for f in ${fonts}; do
	echo "#include \"${f}\""
done
echo "#ifdef __cplusplus"
echo "extern \"C\" {"
echo "#endif"
echo ""
echo "extern FontDescription fonts[];"
echo ""
echo "#ifdef __cplusplus"
echo "} // extern \"C\""
echo "#endif"
echo ""
echo "#endif // __FONT_LIST_H";
exec 3>&-


exec 3<> font_list.c
exec 1>&3
echo "#include \"font_list.h\""
echo ""
echo "FontDescription fonts[] = {"
for f in ${fonts}; do
	c_name="font_${f%.*}"
	echo -n "	{"
	echo -n "\"$(font_name "${f}") $(font_size "${f}")\", "
	echo -n "&${c_name}"
	echo "},"
done
echo "	{0, 0}"
echo "};"
exec 1>&4
echo Done
