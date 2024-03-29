// Copyright (c) 2019 fortiss GmbH
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "modules/models/tests/make_test_world.hpp"

#include "modules/geometry/polygon.hpp"
#include "modules/geometry/line.hpp"
#include "modules/geometry/commons.hpp"
#include "modules/models/behavior/idm/idm_classic.hpp"
#include "modules/commons/params/default_params.hpp"
#include "modules/world/observed_world.hpp"
#include "modules/models/execution/interpolation/interpolate.hpp"
#include "modules/models/behavior/constant_velocity/constant_velocity.hpp"

using namespace modules::models::dynamic;
using namespace modules::models::execution;
using namespace modules::commons;
using namespace modules::models::behavior;
using namespace modules::world::map;
using namespace modules::models::dynamic;
using namespace modules::world;
using namespace modules::geometry;
using namespace modules::world::goal_definition;



WorldPtr modules::models::tests::make_test_world(int num_other_agents, double rel_distance,
                                                 double ego_velocity, double velocity_difference,
                                                 const GoalDefinitionPtr& ego_goal_definition) {
  DefaultParams params;
  ExecutionModelPtr exec_model(new ExecutionModelInterpolate(&params));
  DynamicModelPtr dyn_model(nullptr);
  BehaviorModelPtr beh_model_idm(new BehaviorIDMClassic(&params));
  BehaviorModelPtr beh_model_const(new BehaviorConstantVelocity(&params));

  Polygon polygon(Pose(1.25, 1, 0), std::vector<Point2d>{Point2d(0, 0), Point2d(0, 2), Point2d(4, 2), Point2d(4, 0), Point2d(0, 0)});
  
  State init_state1(static_cast<int>(StateDefinition::MIN_STATE_SIZE));
  init_state1 << 0.0, 1.0, 0.0, 0.0, ego_velocity;
  AgentPtr agent1(new Agent(init_state1, beh_model_idm, dyn_model, exec_model, polygon, &params, ego_goal_definition));

  State init_state2(static_cast<int>(StateDefinition::MIN_STATE_SIZE));
  float rel_dist_vlength = rel_distance + polygon.front_dist_ + polygon.rear_dist_;
  init_state2 << 0.0, 1.0+rel_dist_vlength, 0.0, 0.0, ego_velocity - velocity_difference;
  AgentPtr agent2(new Agent(init_state2, beh_model_const, dyn_model, exec_model, polygon, &params));

  State init_state3(static_cast<int>(StateDefinition::MIN_STATE_SIZE));
  init_state3 << 0.0, 10.0+rel_dist_vlength, 0.0, 0.0, ego_velocity - velocity_difference;
  AgentPtr agent3(new Agent(init_state3, beh_model_const, dyn_model, exec_model, polygon, &params));

  WorldPtr world(new World(&params));
  world->add_agent(agent1);
  if(num_other_agents == 1) {
    world->add_agent(agent2);
  } else if (num_other_agents == 2) {
    world->add_agent(agent3);
  }
  world->UpdateAgentRTree();
  world->set_map(MapInterfacePtr(new DummyMapInterface()));

  // Define some driving corridor from x=1 to x=20, define it in such a way that no agent collides with the corridor initially
    Line center;
  center.add_point(Point2d(-10,0));
  center.add_point(Point2d(1,0));
  center.add_point(Point2d(2,0));
  center.add_point(Point2d(2000,0));

  Line outer;
  outer.add_point(Point2d(-10,3));
  outer.add_point(Point2d(1,3));
  outer.add_point(Point2d(2,3));
  outer.add_point(Point2d(2000,3));

  Line inner;
  inner.add_point(Point2d(-10,-3));
  inner.add_point(Point2d(1,-3));
  inner.add_point(Point2d(2,-3));
  inner.add_point(Point2d(2000,-3));

  DrivingCorridor corridor(outer, inner, center);
  LocalMapPtr local_map(new LocalMap(0, GoalDefinitionPtr(), corridor));
  LocalMapPtr local_map2(new LocalMap(0, GoalDefinitionPtr(), corridor));
  LocalMapPtr local_map3(new LocalMap(0, GoalDefinitionPtr(), corridor));
  agent1->set_local_map(local_map);
  agent2->set_local_map(local_map2);
  agent3->set_local_map(local_map3);
  agent1->UpdateDrivingCorridor(20);
  agent2->UpdateDrivingCorridor(20);
  agent3->UpdateDrivingCorridor(20);

  return WorldPtr(world->Clone());
}

ObservedWorld modules::models::tests::make_test_observed_world(int num_other_agents, double rel_distance, double ego_velocity, double velocity_difference,
                                                              const modules::world::goal_definition::GoalDefinitionPtr& ego_goal_definition) {
  // Create observed world for first agent
  WorldPtr current_world_state = modules::models::tests::make_test_world(num_other_agents, rel_distance, ego_velocity, velocity_difference, ego_goal_definition);
  ObservedWorld observed_world(*(current_world_state), current_world_state->get_agents().begin()->second->get_agent_id());
  return observed_world;
}