// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "modules/world/goal_definition/goal_definition_polygon.hpp"
#include "modules/world/objects/agent.hpp"

namespace modules {
namespace world {
namespace goal_definition {


bool GoalDefinitionPolygon::AtGoal(const modules::world::objects::Agent& agent) const {
    return modules::geometry::Collide(
        agent.GetPolygonFromState(agent.get_current_state()),
        goal_shape_);
}


}  // namespace objects
}  // namespace world
}  // namespace modules