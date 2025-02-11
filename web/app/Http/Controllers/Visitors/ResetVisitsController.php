<?php

namespace App\Http\Controllers\Visitors;

use App\Http\Controllers\Controller;
use App\Models\Visit;
use Illuminate\Support\Facades\Redirect;

class ResetVisitsController extends Controller
{
    public function __invoke()
    {
        Visit::query()->delete();

        return Redirect::back();
    }
}