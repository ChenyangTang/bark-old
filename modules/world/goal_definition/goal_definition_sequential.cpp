// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "modules/world/goal_definition/goal_definition_sequential.hpp"
#include "modules/world/objects/agent.hpp"

namespace modules {
namespace world {
namespace goal_definition {


bool GoalDefinitionSequential::AtGoal(
  const modules::world::objects::Agent& agent) {
  BARK_EXPECT_TRUE (!sequential_goals_.empty());
  // First goal reached?
  if (last_sequential_goal_reached_ == NO_GOAL_REACHED) {
    if (sequential_goals_[0]->AtGoal(agent)) {
        last_sequential_goal_reached_ = 0;
    }
  // Check if next goal reached
  } else {
    // But first check if there are more goals
    if (sequential_goals_.size()-1 >= last_sequential_goal_reached_+1) {
      if (sequential_goals_[last_sequential_goal_reached_+1]->AtGoal(agent)) {
        last_sequential_goal_reached_ = last_sequential_goal_reached_+1;
      }
    }
  }

  // If we arived at the last goal then at goal = true
  if (last_sequential_goal_reached_ == sequential_goals_.size()-1) {
    return true;
  } else {
    return false;
  }
}

GoalDefinitionPtr GoalDefinitionSequential::GetNextGoal(
  const modules::world::objects::Agent& agent) {
  BARK_EXPECT_TRUE (!sequential_goals_.empty());
  if (last_sequential_goal_reached_ == NO_GOAL_REACHED)
    return sequential_goals_[0];

  if (last_sequential_goal_reached_ + 1 < sequential_goals_.size())
    return sequential_goals_[last_sequential_goal_reached_+1];
  return nullptr;
}

}  // namespace goal_definition
}  // namespace world
}  // namespace modules
