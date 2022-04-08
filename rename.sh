for dir in algorithms/*/ algorithms/*/*/
do
  cd $dir
  for file in *.cpp
  do
    base=$(basename $file .cpp)
    mv $file $base.hpp
    printf "#include \"$dir/$base.hpp\"" > $base
  done
  cd -
done
