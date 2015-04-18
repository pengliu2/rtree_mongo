#ifndef __RTREE_DEBUG_H__
#define __RTREE_DEBUG_H__

Entry * createEntryFromDoubles(double left, double lower, double right, double upper, std::unordered_map<int, std::string> newDoc);
int debugDump(Node *current, int level);


#endif /* __RTREE_DEBUG_H__ */
