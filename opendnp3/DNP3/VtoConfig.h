//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  Green Enery Corp licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
#ifndef __VTO_CONFIG_H_
#define __VTO_CONFIG_H_

#include <opendnp3/DNP3/VtoRouterSettings.h>

namespace apl
{
namespace dnp
{

struct VtoRouterConfig {
	VtoRouterConfig() {}

	std::string mPhysicalLayerName;

	VtoRouterSettings mSettings;
};

struct VtoConfig {
	VtoConfig() {}

	void AddVtoRouterConfig(VtoRouterConfig& arSetting) {
		mRouterConfigs.push_back(arSetting);
	}

	std::vector<VtoRouterConfig> mRouterConfigs;
};




}
}

/* vim: set ts=4 sw=4: */

#endif
