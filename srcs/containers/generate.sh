#!/bin/sh
while read cont type name
do
  [ -z "$name" ] && name="$type"_"$cont"
  [ -d "$name" ] || mkdir $name
  [ -z "$type" ] || [ -z "$cont" ] && continue
  def=$(echo "$name" | tr '[:lower:]' '[:upper:]')
  sed <$cont/$cont.h >$name/$name.h -e "s/NAME/$name/g" -e "s/TYPE/$type/g" -e "s/DEF/$def/g"
  sed <$cont/$cont.c >$name/$name.c -e "s/NAME/$name/g" -e "s/TYPE/$type/g"
done