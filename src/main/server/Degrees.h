/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TRITON_DEGREES_H
#define TRITON_DEGREES_H

#include "Server.h"
#include <Graph.h>
#include <seastar/http/function_handlers.hh>
#include <seastar/http/httpd.hh>
#include <seastar/http/json_path.hh>

using namespace seastar;
using namespace httpd;
using namespace triton;

class Degrees {

  class GetDegreeHandler : public httpd::handler_base {
  public:
    explicit GetDegreeHandler(Degrees& degrees) : parent(degrees) {};
  private:
    Degrees& parent;
    future<std::unique_ptr<reply>> handle(const sstring& path, std::unique_ptr<request> req, std::unique_ptr<reply> rep) override;
  };

  class GetDegreeByIdHandler : public httpd::handler_base {
  public:
    explicit GetDegreeByIdHandler(Degrees& degrees) : parent(degrees) {};
  private:
    Degrees& parent;
    future<std::unique_ptr<reply>> handle(const sstring& path, std::unique_ptr<request> req, std::unique_ptr<reply> rep) override;
  };

private:
  Graph& graph;
  GetDegreeHandler getDegreeHandler;
  GetDegreeByIdHandler getDegreeByIdHandler;

public:
  explicit Degrees(Graph &graph) : graph(graph), getDegreeHandler(*this), getDegreeByIdHandler(*this) {}
  void set_routes(routes& routes);
};


#endif//TRITON_DEGREES_H
