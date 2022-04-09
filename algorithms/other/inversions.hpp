#ifndef ALGORITHMS_OTHER_INVERSIONS_HPP
#define ALGORITHMS_OTHER_INVERSIONS_HPP

template <typename T>
long long merge_sort(T *v, T *aux, int l, int r) {
  if (r <= l + 1) return 0;
  int m = (l + r) / 2;
  long long res = merge_sort(v, aux, l, m) + merge_sort(v, aux, m, r);
  int i = l, j = m, k = l;
  while (i < m && j < r) {
    aux[k++] = v[i] <= v[j] ? v[i++] : (res += m - i, v[j++]);
  }
  while (i < m) aux[k++] = v[i++];
  while (j < r) aux[k++] = v[j++];
  while (l < r) {
    v[l] = aux[l];
    ++l;
  }
  return res;
}

template <typename T>
long long count_inversions(std::vector<T> v) {
  std::vector<T> aux(v.size());
  return merge_sort(v.data(), aux.data(), 0, v.size());
}

#endif  // ALGORITHMS_OTHER_INVERSIONS_HPP
