#!/bin/sh
echo "#ifndef MINISHELL_V2_CONTAINERS_H
#define MINISHELL_V2_CONTAINERS_H" > containers.h
while read cont type name
do
  [ -z "$name" ] && name="$type"_"$cont"
  [ -d "$name" ] || mkdir $name
  [ -z "$type" ] || [ -z "$cont" ] && continue
  def=$(echo "$name" | tr '[:lower:]' '[:upper:]')
  sed <$cont/$cont.h >$name/$name.h -e "s/NAME/$name/g" -e "s/TYPE/$type/g" -e "s/DEF/$def/g"
  sed <$cont/$cont.c >$name/$name.c -e "s/NAME/$name/g" -e "s/TYPE/$type/g"
  echo "#include \"$name/$name.h\"" >> containers.h
done

echo "#endif" >> containers.h