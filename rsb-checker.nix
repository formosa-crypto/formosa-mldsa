with (import <nixpkgs> {});
let
    repo =  builtins.fetchGit {
            url = "https://github.com/sarranz/jasmin";
            ref = "rsb3";
            rev = "324715a088a48b2a43bb3a22aafccdfd003992a2";
    };

    jasmin-rsb = import (repo + "/default.nix") { };
in
mkShell {
    buildInputs = [ jasmin-rsb ];
}
