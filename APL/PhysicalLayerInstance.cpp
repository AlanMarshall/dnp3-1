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
#include "PhysicalLayerInstance.h"

#include <map>
#include <string>

#include "PhysicalLayerFactory.h"
#include "IPhysicalLayerAsync.h"

namespace apl
{

PhysLayerInstance::PhysLayerInstance(IPhysicalLayerAsyncFactory aFactory) :
	mFactoryAsync(aFactory),
	mpLayer(NULL),
	mpLogger(NULL),
	mAutoDelete(true)
{

}

PhysLayerInstance::PhysLayerInstance(IPhysicalLayerAsync* apPhys, Logger* apLogger, bool aAutoDelete) :
	mpLayer(apPhys),
	mpLogger(apLogger),
	mAutoDelete(aAutoDelete)
{}

void PhysLayerInstance::Release()
{

	if(mAutoDelete) delete mpLayer;
	SetLayer(NULL, NULL, false);
}

bool PhysLayerInstance::IsCreated()
{
	return mpLayer != NULL;
}

IPhysicalLayerAsync*  PhysLayerInstance::GetLayer(Logger* apLogger, boost::asio::io_service* apService, bool aAutoDelete)
{
	if(mpLayer == NULL) this->SetLayer(mFactoryAsync(apLogger, apService), apLogger, aAutoDelete);
	return mpLayer;
}

void PhysLayerInstance::SetLayer(IPhysicalLayerAsync* apLayer, Logger* apLogger, bool aAutoDelete)
{
	mpLayer = apLayer;
	mpLogger = apLogger;
	mAutoDelete = aAutoDelete;
}


}

