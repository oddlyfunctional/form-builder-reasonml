open Css;

let openSans = fontFamily("'Open Sans', sans-serif");
let montserrat = fontFamily("'Montserrat', sans-serif");

let button = [
  fontSize(em(1.)),
  borderRadius(px(3)),
  textTransform(uppercase),
  cursor(`pointer),
  padding2(~v=em(0.4), ~h=em(1.2)),
  margin(px(5)),
];

let primaryButton = style(merge([button, [
  backgroundColor(hex("246db7")),
  color(white),

  hover([
    backgroundColor(hex("5599dd")),
  ]),
]]));

let secondaryButton = style(merge([button, [
  backgroundColor(white),
  border(px(1), solid, hex("cacaca")),
  color(hex("333333")),

  hover([
    backgroundColor(hex("cacaca")),
  ]),
]]));

let textRight = style([ textAlign(`right) ]);
let textCenter = style([ textAlign(`center) ]);

let table = style([
  borderCollapse(`collapse),
  width(`percent(100.)),
  marginBottom(rem(1.)),

  selector(" thead", [
    montserrat

  ]),

  selector(" tbody", [
    border(px(1), solid, hex("f1f1f1")),

    selector(" tr", [
      backgroundColor(white),

      selector("&:nth-child(even)", [
        backgroundColor(hex("f1f1f1")),
      ]),

      selector(" td", [
        padding3(~top=rem(0.5), ~h=rem(0.625), ~bottom=rem(0.625)),
      ]),
    ]),
  ]),
]);

let choice = style([
  marginRight(em(1.5)),
  cursor(`pointer),
  display(inlineFlex),
  alignItems(center),

  selector(" input[type=radio], input[type=checkbox]", [
    marginRight(px(8)),
  ]),
]);
