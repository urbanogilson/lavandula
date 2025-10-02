set -e

REPO="ashtonjamesd/lavandula"
INSTALL_DIR="/usr/local"
TMP_DIR="/tmp/lavandula-install"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

command_exists() {
    command -v "$1" >/dev/null 2>&1
}

download_source() {
    log_info "Downloading source code..."

    rm -rf "$TMP_DIR"
    mkdir -p "$TMP_DIR"
    cd "$TMP_DIR"

    git clone "https://github.com/${REPO}.git" .
    log_success "Source code downloaded"
}

check_dependencies() {
    if ! command_exists gcc; then
        log_error "GCC is required but not installed. Please install GCC first."
        exit 1
    fi

    if ! command_exists make; then
        log_error "make is required but not installed. Please install make first."
        exit 1
    fi

    if ! command_exists git; then
        log_error "git is required but not installed. Please install git first."
        exit 1
    fi
}

build_project() {
    log_info "Building Lavandula..."
    make
    log_success "Build completed"
}

install_project() {
    log_info "Installing Lavandula to ${INSTALL_DIR}..."
    sudo make PREFIX="$INSTALL_DIR"
    log_success "Installation completed"
}

main() {
    echo "Installing Lavandula Web Framework..."
    check_dependencies
    download_source
    build_project
    install_project



    log_info "Cleaning up temporary files..."
    rm -rf "$TMP_DIR"
    log_success "Cleanup completed"

    log_info "Installation complete"
}

main "$@"