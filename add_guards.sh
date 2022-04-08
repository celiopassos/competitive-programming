for file in algorithms/*/*.hpp algorithms/*/*/*.hpp
do
  guarname=$(sed "s/[\/.]/_/g" <<< ${file^^})
  printf "#ifndef $guarname\n#define $guarname\n\n" > tmp.txt
  cat $file >> tmp.txt
  printf "\n\n#endif  // $guarname\n" >> tmp.txt
  mv tmp.txt $file
done
