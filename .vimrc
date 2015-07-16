set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'gmarik/Vundle.vim'
Plugin 'flazz/vim-colorschemes'
Bundle "pangloss/vim-javascript"
Plugin 'jelera/vim-javascript-syntax'
Plugin 'nathanaelkane/vim-indent-guides'
Plugin 'moll/vim-node'
Bundle 'scrooloose/syntastic'
Bundle 'Valloric/YouCompleteMe'
Bundle 'marijnh/tern_for_vim'
Plugin 'elzr/vim-json'
Bundle 'scrooloose/nerdtree'
Plugin 'wting/rust.vim'
Bundle 'zah/nimrod.vim'
Bundle 'tpope/vim-fugitive'
call vundle#end()

filetype plugin indent on    " required

filetype plugin on
set expandtab
set cindent

set shiftwidth=4
set tabstop=4
set number

autocmd FileType JavaScript setl shiftwidth=2 tabstop=2

vnoremap > >gv
vnoremap < <gv

set incsearch
set hlsearch

set t_Co=256
syntax on

set backspace=indent,eol,start

colorscheme distinguished

let g:indent_guides_auto_colors = 0
autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  guibg=red   ctermbg=3
autocmd VimEnter,Colorscheme * :hi IndentGuidesEven guibg=green ctermbg=4

let g:syntastic_javascript_checkers = ['jscs']
let g:syntastic_always_populate_loc_list = 1
let g:ycm_add_preview_to_completeopt=0
let g:ycm_confirm_extra_conf=0
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
set completeopt-=preview

map <F10> :q!<CR>
imap <F10> <ESC>:q!<CR>

map <F2> :w<CR>
imap <F2> <ESC>:w<CR>
