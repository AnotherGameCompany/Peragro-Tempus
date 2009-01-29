/*
    Copyright (C) 2009 Development Team of Peragro Tempus

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef QUERYHELPER_H
#define QUERYHELPER_H

//#include <wfmath/octree.h>
//
///// Get the union of two queries.
//// 2*(N+M)-1
//QueryResult Union(const QueryResult& a, const QueryResult& b)
//{
//  QueryResult c;
//  std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.begin()));
//  return c;
//}
//
///// Get the difference of two queries.
//// 2*(N+M)-1
//QueryResult Difference(const QueryResult& a, const QueryResult& b)
//{
//  QueryResult c;
//  std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.begin()));
//  return c;
//}
//
///*
// * @param a The old query.
// * @param b The new query.
// * @return a std::pair with .first a QueryResult with new entries
// * and .second a QueryResult with old entries
// */
//std::pair<QueryResult,QueryResult> AddAndDiscard(const QueryResult& a, const QueryResult& b)
//{
//  QueryResult c = Union(a, b);
//
//  //Add: c - a
//  QueryResult add = Difference(c, a);
//
//  //Discard: c - b
//  QueryResult discard = Difference(c, b);
//
//  std::pair<QueryResult,QueryResult> addAndDiscard(add, discard);
//  return addAndDiscard;
//}

#endif // QUERYHELPER_H