#include "body.hpp"


int WormBody::get_angle(int num) {
  auto it = angles_.begin();
  for (int i = 0; i < num; i ++) {it++;}
  return *it;
}

void WormBody::increase_angle(int num) {
  auto it = angles_.begin();
  for (int i = 0; i < num; i ++) {it++;}
  *it += 10;
  count_++;
}

void WormBody::decrease_angle(int num) {
  auto it = angles_.begin();
  for (int i = 0; i < num; i ++) {it++;}
  *it -= 10;
  count_++;
}
