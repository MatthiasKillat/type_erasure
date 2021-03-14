#pragma once

#include <memory>
#include <iostream>
#include <optional>

#include "type_erasure/push_pop_interface.hpp"
#include "concepts/member_func_check.hpp"

//could be generated from the interface
GENERATE_HAS_FUNC(push);
GENERATE_HAS_FUNC(pop);