// Generated by BUCKLESCRIPT VERSION 4.0.7, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Utils$ReactTemplate = require("../Utils.bs.js");
var QuestionField$ReactTemplate = require("./QuestionField.bs.js");

var component = ReasonReact.reducerComponent("NewQuestionnaire");

function make(_children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (param) {
              var send = param[/* send */3];
              return React.createElement("form", undefined, React.createElement("h1", undefined, Utils$ReactTemplate.s("Build your form")), Utils$ReactTemplate.mapi((function (index, question) {
                                  return ReasonReact.element(String(index), undefined, QuestionField$ReactTemplate.make(question, (function (question) {
                                                    return Curry._1(send, /* UpdateQuestion */[
                                                                index,
                                                                question
                                                              ]);
                                                  }), String(index), /* array */[]));
                                }))(param[/* state */1][/* questions */1]), React.createElement("button", {
                              type: "button",
                              onClick: (function (param) {
                                  return Curry._1(send, /* AddQuestion */0);
                                })
                            }, Utils$ReactTemplate.s("Add question")));
            }),
          /* initialState */(function (param) {
              return /* record */[
                      /* description */"",
                      /* questions : [] */0
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (action) {
                var question = action[1];
                var index = action[0];
                return /* Update */Block.__(0, [/* record */[
                            /* description */state[/* description */0],
                            /* questions */List.mapi((function (i, q) {
                                    if (i === index) {
                                      return question;
                                    } else {
                                      return q;
                                    }
                                  }), state[/* questions */1])
                          ]]);
              } else {
                return /* Update */Block.__(0, [/* record */[
                            /* description */state[/* description */0],
                            /* questions */List.append(/* :: */[
                                  /* TextField */Block.__(0, [""]),
                                  /* [] */0
                                ], state[/* questions */1])
                          ]]);
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */
