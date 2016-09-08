set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'gmarik/Vundle.vim'
Plugin 'flazz/vim-colorschemes'
Bundle 'pangloss/vim-javascript'
Plugin 'jelera/vim-javascript-syntax'
Plugin 'nathanaelkane/vim-indent-guides'
Plugin 'moll/vim-node'
Bundle 'Valloric/YouCompleteMe'
Bundle 'marijnh/tern_for_vim'
Plugin 'elzr/vim-json'
Bundle 'scrooloose/nerdtree'
Bundle 'jistr/vim-nerdtree-tabs'
Plugin 'wting/rust.vim'
Bundle 'zah/nimrod.vim'
Bundle 'tpope/vim-fugitive'
Plugin 'wincent/command-t'
Plugin 'godlygeek/tabular'
Plugin 'plasticboy/vim-markdown'
Plugin 'tpope/vim-surround.git'
Plugin 'tpope/vim-repeat'
Bundle 'rdnetto/YCM-Generator'
Plugin 'vim-scripts/L9'
Plugin 'vim-scripts/FuzzyFinder'
Plugin 'mxw/vim-jsx'
Plugin 'rhysd/vim-clang-format'
Plugin 'tikhomirov/vim-glsl'
Plugin 'xolox/vim-misc'
Plugin 'xolox/vim-easytags'
Plugin 'majutsushi/tagbar'

call vundle#end()

filetype plugin indent on    " required

filetype plugin on
set expandtab
set cindent

set shiftwidth=4
set tabstop=4
set number


autocmd FileType javascript setl shiftwidth=2 tabstop=2
autocmd FileType cpp setl shiftwidth=2 tabstop=2

vnoremap > >gv
vnoremap < <gv

set incsearch
set hlsearch

set t_Co=256
syntax on

set backspace=indent,eol,start

colorscheme distinguished

let g:indent_guides_auto_colors=0
autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  guibg=red   ctermbg=3
autocmd VimEnter,Colorscheme * :hi IndentGuidesEven guibg=green ctermbg=4
au BufWinEnter * let w:m1=matchadd('Search', '\%<81v.\%>77v', -1)

" c++
au FileType cpp set makeprg=make\ -j9
au FileType cpp nnoremap <F4> :make!<cr>

set colorcolumn=+1
highlight ColorColumn ctermbg=lightred guibg=lightred

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

" Vim tabs navigation"

map <C-n> :NERDTreeMirrorToggle<CR>
map <C-f> :NERDTreeTabsFind<CR>

