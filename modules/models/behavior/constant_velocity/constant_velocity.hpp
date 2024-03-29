// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef MODULES_MODELS_BEHAVIOR_CONSTANT_VELOCITY_CONSTANT_VELOCITY_HPP_
#define MODULES_MODELS_BEHAVIOR_CONSTANT_VELOCITY_CONSTANT_VELOCITY_HPP_

#include "modules/models/behavior/longitudinal_acceleration/longitudinal_acceleration.hpp"
#include "modules/world/world.hpp"

namespace modules {
namespace models {
namespace behavior {

using dynamic::Trajectory;
using world::objects::AgentId;
using world::ObservedWorld;

class BehaviorConstantVelocity : public BehaviorLongitudinalAcceleration {
 public:
  explicit BehaviorConstantVelocity(commons::Params *params) :
    BehaviorLongitudinalAcceleration(params) {}

  virtual ~BehaviorConstantVelocity() {}

  Trajectory Plan(float delta_time,
                  const ObservedWorld& observed_world) { return BehaviorLongitudinalAcceleration::Plan(delta_time, observed_world); };

  virtual double CalculateLongitudinalAcceleration(const ObservedWorld& observed_world) {return 0.0f;}

  virtual BehaviorModel *Clone() const;
};

inline BehaviorModel *BehaviorConstantVelocity::Clone() const {
  return new BehaviorConstantVelocity(*this);
}

}  // namespace behavior
}  // namespace models
}  // namespace modules

#endif  // MODULES_MODELS_BEHAVIOR_CONSTANT_VELOCITY_CONSTANT_VELOCITY_HPP_
