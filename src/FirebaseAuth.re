[@bs.module "react-firebaseui/StyledFirebaseAuth"]
external styledFirebaseAuth: ReasonReact.reactClass = "default";

type providerId;
type auth;

[@bs.deriving abstract]
type authProvider = {
  [@bs.as "PROVIDER_ID"] id: providerId,
};

[@bs.module "firebase"] [@bs.scope "auth"] [@bs.val]
external google: authProvider = "GoogleAuthProvider";

[@bs.module "firebase"] [@bs.scope "auth"] [@bs.val]
external email: authProvider = "EmailAuthProvider";

[@bs.module "firebase"] [@bs.val]
external auth: unit => auth = "";

[@bs.deriving abstract]
type uiConfig = {
  signInFlow: string,
  signInSuccessUrl: string,
  signInOptions: array(providerId),
};

let config = uiConfig(
  ~signInFlow="popup",
  ~signInSuccessUrl="/",
  ~signInOptions=[|google->idGet, email->idGet|],
);

[@bs.deriving abstract]
type jsProps = {
  uiConfig: uiConfig,
  firebaseAuth: auth,
};

let make = children =>
  ReasonReact.wrapJsForReason(
    ~reactClass=styledFirebaseAuth,
    ~props=jsProps(
      ~uiConfig=config,
      ~firebaseAuth=auth(),
    ),
    children,
  );
