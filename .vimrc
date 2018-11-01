set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'gmarik/Vundle.vim'
Plugin 'isRuslan/vim-es6'
Plugin 'nathanaelkane/vim-indent-guides'
Plugin 'moll/vim-node'
Plugin 'altercation/vim-colors-solarized'
Plugin 'vim-syntastic/syntastic'
Bundle 'Valloric/YouCompleteMe'
Plugin 'elzr/vim-json'
Bundle 'scrooloose/nerdtree'
Bundle 'jistr/vim-nerdtree-tabs'
Bundle 'zah/nimrod.vim'
Bundle 'tpope/vim-fugitive'
Plugin 'wincent/command-t'
Plugin 'godlygeek/tabular'
Plugin 'tikhomirov/vim-glsl'
Plugin 'plasticboy/vim-markdown'
Plugin 'tpope/vim-surround.git'
Plugin 'tpope/vim-repeat'
Bundle 'rdnetto/YCM-Generator'
Plugin 'vim-scripts/L9'
Plugin 'vim-scripts/FuzzyFinder'
Plugin 'rhysd/vim-clang-format'
Plugin 'majutsushi/tagbar'
Plugin 'ternjs/tern_for_vim'
Plugin 'krisajenkins/vim-projectlocal'
Plugin 'leafgarland/typescript-vim'
Plugin 'rust-lang/rust.vim'
Plugin 'yegappan/grep'
Plugin 'racer-rust/vim-racer'
Plugin 'Quramy/tsuquyomi'

set exrc

cd $HOME/projects

call vundle#end()

filetype plugin indent on    " required
filetype plugin on

set expandtab
set cindent

set shiftwidth=4
set tabstop=4
set number


autocmd FileType typescript setl shiftwidth=2 tabstop=2
autocmd FileType javascript setl shiftwidth=2 tabstop=2
autocmd FileType cpp setl shiftwidth=2 tabstop=2
autocmd FileType rust setl shiftwidth=2 tabstop=2

vnoremap > >gv
vnoremap < <gv

set incsearch
set hlsearch

set t_Co=256
syntax on

set backspace=indent,eol,start
set background=dark
set backupcopy=yes
set foldmethod=indent

colorscheme solarized
set guifont=Menlo\ Regular:h14
set guioptions-=T
set guioptions-=r
set guioptions-=L

"set statusline+=%#warningmsg#
"set statusline+=%{SyntasticStatuslineFlag()}
"set statusline+=%*
let Grep_Default_Filelist = '*.c *.cpp *.asm *.js *.ts *.jsx' 
let Grep_Skip_Dirs = 'node_modules .git' 

let g:indent_guides_auto_colors=0
let g:solarized_termcolors=255
let g:syntastic_check_on_open=1
let g:syntastic_always_populate_loc_list = 1
let g:syntastic_javascript_checkers=['eslint']
let g:syntastic_typescript_checkers=['tsuquyomi']
let g:syntastic_javascript_eslint_exe='npx eslint'
let g:syntastic_rust_checkers=['cargo']
let g:syntastic_debug=0
let g:rustc_path = $HOME."/.cargo/bin/rustc"
let g:racer_cmd="~/.cargo/bin/racer"
let g:tsuquyomi_disable_default_mappings=1
let g:tsuquyomi_disable_quickfix=1
let g:tsuquyomi_ignore_missing_modules=1

autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  guibg=red   ctermbg=3

autocmd VimEnter,Colorscheme * :hi IndentGuidesEven guibg=green ctermbg=4
autocmd User fugitive command! -bar -buffer -nargs=* Gcm :Gcommit --no-verify

" c++
au FileType cpp set makeprg=make\ -j9
au FileType cpp nnoremap <F4> :make!<cr>

au FileType rust nmap gd <Plug>(rust-def)
au FileType rust nmap gs <Plug>(rust-def-split)
au FileType rust nmap gx <Plug>(rust-def-vertical)
au FileType rust nmap <leader>gd <Plug>(rust-doc)
au FileType typescript map ˆ :TsuDefinition <CR>

set colorcolumn=+1
highlight ColorColumn
set textwidth=80

let g:ctrlk_clang_library_path="/usr/lib/llvm-3.6/lib/"


let g:ycm_global_ycm_extra_conf='~/.ycm_extra_conf.py'                      
let g:ycm_confirm_extra_conf=1

let g:clang_format#command='clang-format'
nmap <F3> :call GetCtrlKState()<CR>
nmap <C-k> :call CtrlKNavigateSymbols()<CR>
nmap <F2> :call CtrlKGoToDefinition()<CR>
nmap <F12> :call CtrlKGetReferences()<CR>
set completeopt-=preview

set directory=./.backup//,/tmp//,.


map <F10> :q!<CR>
imap <F10> <ESC>:q!<CR>

map <F2> :w<CR>
imap <F2> <ESC>:w<CR>

" Navigation 
"
noremap <C-Down>  <C-W>j
noremap <C-Up>    <C-W>k
noremap <C-Left>  <C-W>h
noremap <C-Right> <C-W>l
inoremap § <esc>

" Vim tabs navigation"

map <leader>n :NERDTreeMirrorToggle<CR>
map <leader>f :NERDTreeTabsFind<CR>
