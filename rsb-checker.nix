let
    pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/6dbbd5a2622d9abf9263a5cb0a85ca218974b085.tar.gz") {};
    repo =  builtins.fetchGit {
            url = "https://github.com/sarranz/jasmin";
            ref = "rsb3";
            rev = "324715a088a48b2a43bb3a22aafccdfd003992a2";
    };

    jasmin-rsb = import (repo + "/default.nix") {};
in
pkgs.mkShell {
    buildInputs = [ jasmin-rsb ];
}
