/*
    mergenetsort - A qsort replacement for glibc using sorting networks
    and mergesort
    Copyright (C) 2018  Philipp Knirsch <philippknirsch@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

void netsort2(void *d, size_t size, int (*compar)(const void *, const void *));
void netsort3(void *d, size_t size, int (*compar)(const void *, const void *));
void netsort4(void *d, size_t size, int (*compar)(const void *, const void *));
void netsort5(void *d, size_t size, int (*compar)(const void *, const void *));
void netsort6(void *d, size_t size, int (*compar)(const void *, const void *));
void netsort7(void *d, size_t size, int (*compar)(const void *, const void *));
void netsort8(void *d, size_t size, int (*compar)(const void *, const void *));
void netsort9(void *d, size_t size, int (*compar)(const void *, const void *));
void netsort10(void *d, size_t size, int (*compar)(const void *, const void *));

void merge(void *d, void *s1, void *s2, size_t c1, size_t c2, size_t size, int (*compar)(const void *, const void *));

void mergesort(void *d, size_t n, size_t size, int (*compar)(const void *, const void *));
