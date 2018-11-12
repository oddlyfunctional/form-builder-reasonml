open Utils;

module Style {
  open Css;

  global("body", [
    minHeight(`percent(100.)),
    Styles.openSans,
    lineHeight(em(1.5)),
    color(hex("333333")),
  ]);

  global("html", [
    height(`percent(100.)),
  ]);

  global("h1, h2, h3, h4, h5, h6, label", [
    Styles.montserrat,
    fontWeight(700),
    marginTop(rem(0.2)),
    marginBottom(rem(0.5)),
  ]);

  global("h1", [ fontSize(rem(1.5)) ]);
  global("h2", [ fontSize(rem(1.25)) ]);

  global("a", [
    color(hex("1779ba")),
    textDecoration(`none),
    cursor(`pointer),
  ]);

  global("label", [
    fontSize(rem(1.2)),
    display(inlineBlock),
  ]);

  global("input[type=text], textarea", [
    padding2(~v=rem(0.8), ~h=rem(1.2)),
    border(px(1), solid, hex("cacaca")),
    marginRight(em(1.)),
    fontSize(rem(1.2)),
  ]);

  let wrapper = style([
    backgroundColor(hex("f8f9fa")),
    minHeight(`vh(100.)),
    padding(em(2.)),
  ]);

  let container = style([
    backgroundColor(white),
    padding(em(1.5)),

    media("(min-width: 78px)", [
      maxWidth(px(1140)),
      marginLeft(`auto),
      marginRight(`auto),
    ]),
    media("(max-width: 767px)", [
      maxWidth(`percent(100.)),
      padding(em(1.0)),
    ]),
  ]);
};

let component = ReasonReact.statelessComponent("App");
let make = (_children) => {
  ...component,
  render: _self =>
    <div className=Style.wrapper>
      <div className=Style.container>
        <div>
          <Link href="/">(s("Home"))</Link>
        </div>

        <AppContext.Provider>
          <Router />
        </AppContext.Provider>
      </div>
    </div>
};
