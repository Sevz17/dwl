# Maintainer: Leonardo Hernández <leohdz172@outlook.com>
pkgname=dwl
pkgver=0.2
pkgrel=1
pkgdesc="dwm for wayland"
arch=('x86_64')
url="https://github.com/Sevz17/dwl.git"
license=('MIT')
depends=('wayland-protocols' 'wlroots')
source=("$pkgname-$pkgver.tar.gz")
sha256sums=('SKIP')

build() {
  cd "$srcdir/$pkgname-$pkgver"
  make
}

package() {
  cd "$srcdir/$pkgname-$pkgver"
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D LICENSE.dwm "$pkgdir/usr/share/licenses/$pkgname/LICENSE.dwm"
  install -m644 -D LICENSE.tinywl "$pkgdir/usr/share/licenses/$pkgname/LICENSE.tinywl"
  install -m644 -D README.md "$pkgdir/usr/share/doc/$pkgname/README"
  install -m644 -D applied_patches.txt "$pkgdir/usr/share/doc/$pkgname/applied_patches.txt"
}
