const {src, dest, watch} = require('gulp');
const cp = require('child_process');
const fs = require('fs');

exports.build = async function build() {
  console.log('Starting build...')
  const rebuild = fs.existsSync('./gyp/build/atrijs.vcxproj');
  cp.execSync(`node-gyp -C ./gyp ${rebuild ? 're' : ''}build`);
  src('gyp/build/**/*.node')
    .pipe(dest('./build'));
};

exports.debug = async function() {
  watch('./gyp/src/**/*.{cpp,h}', {delay: 1000}, exports.build);
}