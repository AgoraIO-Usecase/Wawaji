var gulp = require('gulp'),
    htmlmin = require('gulp-htmlmin'),
    uglify = require("gulp-uglify"),
    cssnano = require('gulp-cssnano'),
    concat = require("gulp-concat"),
    rename = require('gulp-rename'),
    imagemin = require('gulp-imagemin'),
    pngquant = require('imagemin-pngquant'),
    order = require('gulp-order'),
    babel = require('gulp-babel'),
    del = require('del');

gulp.task('clean', function() {
    del(['dist/*']);
});

gulp.task('images', function() {
    gulp.src(['src/assets/*.png'])
        .pipe(gulp.dest('dist/assets'));

    gulp.src('src/assets/css/images/*')
        .pipe(gulp.dest('dist/assets/css/images'));

    return gulp.src('src/images/*')
        .pipe(imagemin({
            progressive: true,
            svgoPlugins: [{ removeViewBox: false }],
            use: [pngquant()]
        }))
        .pipe(gulp.dest('dist/assets/images'));
});

gulp.task('fonts', function() {
    return gulp.src([
            'src/assets/fonts/MaterialIcons-Regular.*'
        ])
        .pipe(gulp.dest('dist/assets/fonts/'));
});

gulp.task('sound', function() {
    return gulp.src([
            'src/sound/*.mp3'
        ])
        .pipe(gulp.dest('dist/assets/sound/'));
});

gulp.task('jsmin', function() {

    gulp.src('./src/assets/js/*.js')
        // .pipe(uglify())
        .pipe(babel({
            presets: ['env']
		}))
        .pipe(gulp.dest('./dist/assets/js'));

    return gulp.src('./src/assets/vendor/*.js')
        .pipe(order([
            'jquery*.js',
            'adapter.js',
            'popper.js',
            'bootstrap-material-design.min.js',
            '*.js'
        ]))
        .pipe(concat("vendor-all.js"))
        // .pipe(uglify())
        .pipe(rename('vendor-bundle.js'))
        .pipe(gulp.dest('./dist/assets/js'));
});

gulp.task('cssmin', function() {
    return gulp.src('./src/assets/css/*.css')
        .pipe(order([
            '*.css'
        ]))
        .pipe(concat('all-styles.css'))
        //.pipe(cssnano())
        .pipe(rename('bundle.css'))
        .pipe(gulp.dest('./dist/assets/css'));
});

gulp.task('htmlmin', function() {
    return gulp.src('src/*.html')
        .pipe(htmlmin({ collapseWhitespace: true }))
        .pipe(gulp.dest('./dist'))
});

gulp.task('watch', function() {
    gulp.watch('src/**/*', ['build']);
});

gulp.task("build", ['jsmin', 'cssmin', 'htmlmin', 'images', 'fonts', 'sound']);

gulp.task("default", ['watch']);