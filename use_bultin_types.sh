for file in */*.cpp */*/*.cpp
do
  sed -i 's/uint32_t/unsigned int/g' $file
  sed -i 's/uint64_t/unsigned long long/g' $file
  sed -i 's/int64_t/long long/g' $file
done
